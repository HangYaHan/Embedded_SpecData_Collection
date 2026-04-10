#include "protocol.hpp"

namespace common {

std::string buildHelloMessage(const std::string& runId) {
    // 这里应该把 run_id 序列化成网络消息。
    return "HELLO " + runId;
}

std::string buildStartCycleMessage(const app::CycleRequest& request) {
    // 这里应该把 cycle_id、前序 cycle_id 等字段序列化。
    (void)request;
    return {};
}

app::CycleAck parseCycleAck(const std::string& message) {
    // 这里应该把 ACK 消息解析成结构体。
    (void)message;
    return app::CycleAck{};
}

} // namespace common
