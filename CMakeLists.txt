cmake_minimum_required(VERSION 3.16)
project(EmbeddedSpecDataCollection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(slave
    slave/main.cpp
    slave/slave_app.cpp
    common/config.cpp
    common/logging.cpp
    common/protocol.cpp
)
target_include_directories(slave PRIVATE common)

if(WIN32)
    target_link_libraries(slave PRIVATE ws2_32)
endif()

add_executable(master
    master/main.cpp
    master/master_app.cpp
    master/master_link.cpp
    common/config.cpp
    common/logging.cpp
    common/protocol.cpp
)
target_include_directories(master PRIVATE common)

if(WIN32)
    target_link_libraries(master PRIVATE ws2_32)
endif()
