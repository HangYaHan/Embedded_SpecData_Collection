#include "master_link.hpp"

namespace master {

bool connectToSlave(const std::string& slaveIp, int slavePort) {
    // 这里应该建立 TCP 连接，并准备后续通信。
    (void)slaveIp;
    (void)slavePort;
    return true;
}

bool sendHello(const std::string& runId) {
    // 这里应该发送握手消息并等待 ACK。
    (void)runId;
    return true;
}

bool sendStartCycle(const app::CycleRequest& request) {
    // 这里应该把当前 cycle 的关键信息发送给 slave。
    (void)request;
    return true;
}

app::CycleAck waitForAck(int cycleId) {
    // 这里应该阻塞等待 slave 回执并解析消息内容。
    (void)cycleId;
    return app::CycleAck{};
}

void stopSlave(const std::string& runId) {
    // 这里应该通知 slave 任务结束。
    (void)runId;
}

} // namespace master
