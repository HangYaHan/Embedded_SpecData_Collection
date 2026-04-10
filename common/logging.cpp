#include "logging.hpp"

#include <iostream>

namespace common {

void initLogger(const std::string& runId) {
    // 这里应该创建日志目录并初始化日志文件句柄。
    (void)runId;
}

void logInfo(const std::string& message) {
    // 这里应该把信息写入日志系统。
    std::cout << "[INFO] " << message << std::endl;
}

void logWarn(const std::string& message) {
    // 这里应该把告警写入日志系统。
    std::cout << "[WARN] " << message << std::endl;
}

void logError(const std::string& message) {
    // 这里应该把错误写入日志系统。
    std::cerr << "[ERROR] " << message << std::endl;
}

} // namespace common
