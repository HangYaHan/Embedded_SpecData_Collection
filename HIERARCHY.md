# File Hierarchy and Call Flow

This repository is split into three layers:

1. `common/` - shared data structures, config, logging, and message protocol helpers
2. `master/` - Windows-side orchestration entry points and master-specific workflow stubs
3. `slave/` - Raspberry Pi-side orchestration entry points and sensor workflow stubs

## Directory Layout

```text
CMakeLists.txt
PLAN.md
HIERARCHY.md
common/
    app_types.hpp
    config.hpp
    config.cpp
    logging.hpp
    logging.cpp
    protocol.hpp
    protocol.cpp
    net_utils.hpp
master/
    main.cpp
    master_app.hpp
    master_app.cpp
    master_link.hpp
    master_link.cpp
slave/
    main.cpp
    slave_app.hpp
    slave_app.cpp
```

## Call Flow

### master executable

1. `main()` reads the config path from the command line.
2. `master::runMaster()` orchestrates the whole master workflow.
3. `common::loadConfig()` loads runtime settings.
4. `common::initLogger()` prepares logging.
5. `master::connectToSlave()` establishes the session.
6. `master::sendHello()` performs startup handshake.
7. For each cycle:
   1. `master::buildLedSequence()` creates the LED payload.
   2. `master::sendLedSequence()` sends LED data to serial.
   3. `master::captureSpectrum()` runs Ocean Direct capture.
   4. `master::sendStartCycle()` notifies the slave.
   5. `master::waitForAck()` waits for the slave response.
   6. `common::buildStartCycleMessage()` and `common::parseCycleAck()` support message formatting.

### slave executable

1. `main()` reads the config path from the command line.
2. `slave::runSlave()` orchestrates the whole slave workflow.
3. `common::loadConfig()` loads runtime settings.
4. `common::initLogger()` prepares logging.
5. For each command from master:
   1. `slave::validateCycleOrder()` checks cycle continuity.
   2. `slave::captureSensorData()` reads GPIO data.
   3. `slave::saveSensorData()` persists the sensor file.
   4. `slave::countSavedFiles()` updates file count for ACK.

## Stub Policy

Every function in the current skeleton is intentionally empty or returns a placeholder value.
The purpose is to provide a clean implementation map before filling in real network, serial,
Ocean Direct, and GPIO logic.
