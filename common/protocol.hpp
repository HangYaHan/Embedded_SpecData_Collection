#pragma once

#include <string>

#include "app_types.hpp"

namespace common {

// 构造启动握手消息。
std::string buildHelloMessage(const std::string& runId);

// 构造开始采集消息。
std::string buildStartCycleMessage(const app::CycleRequest& request);

// 解析从机回执消息。
app::CycleAck parseCycleAck(const std::string& message);

} // namespace common
