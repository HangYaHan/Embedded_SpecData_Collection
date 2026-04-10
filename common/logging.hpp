#pragma once

#include <string>

namespace common {

// 初始化日志系统，准备写入主日志或从日志。
void initLogger(const std::string& runId);

// 记录普通信息日志。
void logInfo(const std::string& message);

// 记录告警日志。
void logWarn(const std::string& message);

// 记录错误日志。
void logError(const std::string& message);

} // namespace common
