#pragma once

#include <string>

#include "app_types.hpp"

namespace master {

// 执行 master 侧完整的一轮调度：串口、采谱、通知从机、对账。
int runMaster(const std::string& configPath);

// 生成某个 cycle 的 LED 序列。
app::LedSequence buildLedSequence(const app::AppConfig& config, int cycleId);

// 将 LED 序列发送到串口设备。
bool sendLedSequence(const std::string& serialPort, int baudrate, const app::LedSequence& sequence);

// 调用 Ocean Direct 采集光谱并保存。
std::string captureSpectrum(const app::AppConfig& config, int cycleId);

} // namespace master
