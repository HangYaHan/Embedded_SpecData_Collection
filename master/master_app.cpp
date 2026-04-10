#include "master_app.hpp"

#include <string>

#include "config.hpp"
#include "logging.hpp"
#include "protocol.hpp"

namespace master {

int runMaster(const std::string& configPath) {
    // 这里应该读取配置、初始化资源，并按 cycle 驱动整个 master 流程。
    (void)configPath;
    return 0;
}

app::LedSequence buildLedSequence(const app::AppConfig& config, int cycleId) {
    // 这里应该根据随机策略或表驱动策略生成 LED 序列。
    (void)config;
    (void)cycleId;
    return app::LedSequence{};
}

bool sendLedSequence(const std::string& serialPort, int baudrate, const app::LedSequence& sequence) {
    // 这里应该打开串口并发送 LED 控制命令。
    (void)serialPort;
    (void)baudrate;
    (void)sequence;
    return true;
}

std::string captureSpectrum(const app::AppConfig& config, int cycleId) {
    // 这里应该调用 Ocean Direct SDK 并把光谱保存到指定目录。
    (void)config;
    (void)cycleId;
    return {};
}

} // namespace master
