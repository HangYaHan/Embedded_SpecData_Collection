# Embedded SpecData Collection - Learning Demo

This repository now contains a minimal C++ master/slave network Hello World demo.

## What this demo proves

The demo proves one thing only:

- master can send a signal (`HELLO <cycle_id>`) to slave
- slave can receive the signal and send back (`ACK <cycle_id>`)
- master can verify the ACK and report success

No sensor, GPIO, USB serial, or Ocean Direct code is included yet.

## Build

From repository root:

```bash
cmake -S . -B build
cmake --build build
```

## Run on one machine (quick test)

Terminal A:

```bash
./build/slave 5000
```

Terminal B:

```bash
./build/master 127.0.0.1 5000 1
```

Expected result in master output:

- `[master] received: ACK 1`
- `[master] signal loop SUCCESS`

## Run across Windows (master) and Raspberry Pi (slave)

1. Build the project on each machine.
2. On Raspberry Pi, run slave with a chosen port (for example `5000`).
3. On Windows, run master and pass Raspberry Pi IP + same port.
4. If connect fails, check firewall and campus network policy for inbound port access.

## Source layout

- `common/net_utils.hpp`: small cross-platform socket helpers
- `slave/main.cpp`: TCP server, receives HELLO and returns ACK
- `master/main.cpp`: TCP client, sends HELLO and validates ACK

## Next learning step

After this loop is stable, add a small text log with timestamp and cycle id on both sides.
