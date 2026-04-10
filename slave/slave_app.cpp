#include "slave_app.hpp"

#include <string>

#include "config.hpp"
#include "logging.hpp"

namespace slave {

int runSlave(const std::string& configPath) {
    // 这里应该启动网络服务，并处理 HELLO / START_CYCLE / STOP 消息。
    (void)configPath;
    return 0;
}

bool validateCycleOrder(int expectedPrevCycleId, int localLastCycleId) {
    // 这里应该检查 master 下发的轮次和本地状态是否连续。
    return expectedPrevCycleId == localLastCycleId;
}

std::string captureSensorData(const app::AppConfig& config, int cycleId) {
    // 这里应该从 GPIO 读取一组传感器数据。
    (void)config;
    (void)cycleId;
    return {};
}

std::string saveSensorData(const app::AppConfig& config, int cycleId, const std::string& sensorData) {
    // 这里应该把传感器数据写入文件并返回路径。
    (void)config;
    (void)cycleId;
    (void)sensorData;
    return {};
}

int countSavedFiles(const app::AppConfig& config, const std::string& runId) {
    // 这里应该统计当前 run 已保存的数据文件数量。
    (void)config;
    (void)runId;
    return 0;
}

} // namespace slave
