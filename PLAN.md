## 目标

完成一个可连续运行上千次的自动化采集系统，每轮 cycle 同时完成：

1. Windows(master) 通过 USB 串口发送 LED 控制序列
2. Windows(master) 调用 Ocean Direct 采集光谱并保存
3. Raspberry Pi(slave) 采集 GPIO 传感器数据并保存

核心难点不是功能，而是 **跨设备同步与对账**。

---

## 架构与职责

### Master (Windows)

1. 读取配置文件并初始化
2. 串口发送 LED 序列
3. 调用 Ocean Direct 采谱
4. 向 slave 下发本轮 cycle 信息
5. 接收 slave 回执并做一致性检查
6. 写入主日志与失败重试记录
7. 数据保存在./data

### Slave (Raspberry Pi)

1. 启动 TCP/UDP 服务（建议 TCP）
2. 接收 master 的采集指令
3. 校验 cycle_id 连续性
4. 采集并保存传感器数据
5. 返回 ACK + 保存结果 + 文件计数
6. 写入从日志
7. 数据保存在./data

---

## 配置文件设计（config）

建议使用 `yaml` 或 `json`，最少包含：

1. 基础参数
   - run_id（本次任务编号）
   - total_cycles（总循环次数）
   - retry_max（失败最大重试次数）
   - timeout_ms（各阶段超时时间）
2. Master 侧参数
   - serial_port（如 COM3）
   - serial_baudrate
   - spectrum_save_dir
   - ocean_integration_time_ms
3. Slave 侧参数
   - slave_ip
   - slave_port
   - sensor_save_dir
4. LED 策略
   - mode: random | table
   - seed（随机种子，可复现）
   - table_path（若 mode=table）
5. 命名与对账策略
   - file_naming: by_cycle_id
   - strict_counter_check: true

---

## 数据与通信协议

统一使用 `cycle_id` 作为唯一索引，避免“靠文件个数猜测状态”。

### 消息类型

1. `HELLO`：连通性测试（启动前）
2. `START_CYCLE`：主机通知从机开始某一轮
3. `ACK_CYCLE`：从机返回该轮结果
4. `HEARTBEAT`：长任务保活（可选）
5. `STOP`：任务结束

### START_CYCLE 建议字段

1. run_id
2. cycle_id
3. expected_prev_cycle_id（用于连续性校验）

### ACK_CYCLE 建议字段

1. run_id
2. cycle_id
3. slave_status（ok / fail）
4. slave_file_count
5. error_code / error_message

---

## 单次循环计划（执行时序）

### Before loop: 环境检查

1. master/slave 网络握手成功
2. 串口可打开
3. Ocean Direct 设备可用
4. 保存目录存在且可写

### Stage 1: LED 下发（Master）

1. 根据策略生成 `led_sequence`
2. 发送到串口设备
3. 若失败：重试；超过阈值记失败并终止该轮

### Stage 2: 光谱采集（Master）

1. 调用 Ocean Direct 采集
2. 按 `run_id/cycle_id` 保存文件
3. 得到与 `master_file_count`

### Stage 3: 通知从机（Master -> Slave）

1. 发送 `START_CYCLE(run_id, cycle_id, expected_prev_cycle_id)`
2. 启动等待 ACK 的超时计时器

### Stage 4: 传感器采集（Slave）

1. 校验 `expected_prev_cycle_id == local_last_cycle_id`
2. 校验失败：返回 fail（不同步）
3. 校验通过：采集 GPIO 传感器数据
4. 保存 `sensor_cycle_{cycle_id}.csv`
5. 返回 `ACK_CYCLE(ok, slave_file_count)`

### Stage 5: 对账（Master）

1. 收到 ACK 且 status=ok
2. 校验 `ack.cycle_id == current_cycle_id`
3. 可选校验：`slave_file_count == cycle_id + 1`
4. 记录本轮 `SUCCESS`

### Stage 6: 失败处理

1. 任一阶段失败 -> 标记 `FAILED_STAGE`
2. 若 retry_count < retry_max -> 重试该轮
3. 超过重试上限 -> 记录 `HARD_FAIL`，可选择停止全局任务

---

## 文件组织建议

manifest 示例字段：

1. run_id
2. cycle_id
3. led_sequence
4. spectrum_file_path
5. sensor_file_path
6. start_ts / end_ts / duration_ms
7. status（SUCCESS / HARD_FAIL）
8. error

---

## 最小可行里程碑（MVP）

1. 先做连通性：HELLO/ACK 往返（只跑网络）
2. 再接入 LED 串口（不采谱不采传感器）
3. 再接入 Ocean Direct（master 本地闭环）
4. 再接入 slave 传感器采集
5. 最后加超时、重试、日志与 manifest 对账