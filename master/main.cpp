#include <string>

#include "master_app.hpp"

int main(int argc, char** argv) {
    // 这里只负责把命令行参数转发给 master 编排入口。
    std::string configPath = "config/master.json";
    if (argc >= 2) {
        configPath = argv[1];
    }

    return master::runMaster(configPath);
}
