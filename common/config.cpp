#include "config.hpp"

namespace common {

app::AppConfig loadConfig(const std::string& configPath) {
    // 这里应该解析 yaml/json 配置文件，并填充运行参数。
    (void)configPath;
    return app::AppConfig{};
}

} // namespace common
