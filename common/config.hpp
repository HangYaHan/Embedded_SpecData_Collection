#pragma once

#include <string>

#include "app_types.hpp"

namespace common {

// 读取配置文件并将其转换为运行时配置结构体。
app::AppConfig loadConfig(const std::string& configPath);

} // namespace common
