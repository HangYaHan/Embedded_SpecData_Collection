#pragma once

#include <string>

#include "app_types.hpp"

namespace slave {

// 启动 slave 侧服务，并循环处理来自 master 的命令。
int runSlave(const std::string& configPath);

// 校验当前 cycle 是否和本地状态一致。
bool validateCycleOrder(int expectedPrevCycleId, int localLastCycleId);

// 采集一组 GPIO 传感器数据。
std::string captureSensorData(const app::AppConfig& config, int cycleId);

// 保存传感器数据并返回保存路径。
std::string saveSensorData(const app::AppConfig& config, int cycleId, const std::string& sensorData);

// 统计当前 run 的文件数量。
int countSavedFiles(const app::AppConfig& config, const std::string& runId);

} // namespace slave
