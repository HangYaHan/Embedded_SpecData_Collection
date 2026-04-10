#pragma once

#include <string>
#include <vector>

namespace app {

struct AppConfig {
    std::string run_id;
    int total_cycles = 0;
    int retry_max = 0;
    int timeout_ms = 0;
    std::string data_root = "./data";
};

struct LedSequence {
    std::vector<int> values;
};

struct CycleRequest {
    std::string run_id;
    int cycle_id = 0;
    int expected_prev_cycle_id = -1;
};

struct CycleAck {
    std::string run_id;
    int cycle_id = 0;
    std::string slave_status;
    int slave_file_count = 0;
    std::string error_code;
    std::string error_message;
};

struct CycleManifest {
    std::string run_id;
    int cycle_id = 0;
    std::string led_sequence;
    std::string spectrum_file_path;
    std::string sensor_file_path;
    std::string start_ts;
    std::string end_ts;
    std::string status;
    std::string error;
};

} // namespace app
