#pragma once

#include <string>

#include "app_types.hpp"

namespace master {

// 连接到 slave 并建立会话。
bool connectToSlave(const std::string& slaveIp, int slavePort);

// 向 slave 发送启动握手消息。
bool sendHello(const std::string& runId);

// 发送单轮采集消息。
bool sendStartCycle(const app::CycleRequest& request);

// 等待并解析 slave 的 ACK。
app::CycleAck waitForAck(int cycleId);

// 结束与 slave 的会话。
void stopSlave(const std::string& runId);

} // namespace master
