#include <string>

#include "slave_app.hpp"

int main(int argc, char** argv) {
    // 这里只负责把命令行参数转发给 slave 编排入口。
    std::string configPath = "config/slave.json";
    if (argc >= 2) {
        configPath = argv[1];
    }

    return slave::runSlave(configPath);
}
