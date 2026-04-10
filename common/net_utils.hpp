#pragma once

#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using SocketHandle = SOCKET;
constexpr SocketHandle kInvalidSocket = INVALID_SOCKET;
#else
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using SocketHandle = int;
constexpr SocketHandle kInvalidSocket = -1;
#endif

namespace net {

inline bool initSockets(std::string& err) {
#ifdef _WIN32
    WSADATA wsaData{};
    const int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc != 0) {
        err = "WSAStartup failed: " + std::to_string(rc);
        return false;
    }
#else
    (void)err;
#endif
    return true;
}

inline void cleanupSockets() {
#ifdef _WIN32
    WSACleanup();
#endif
}

inline void closeSocket(SocketHandle sock) {
#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
}

inline std::string lastErrorMessage(const std::string& where) {
#ifdef _WIN32
    return where + " failed with error " + std::to_string(WSAGetLastError());
#else
    return where + " failed: " + std::strerror(errno);
#endif
}

inline bool sendAll(SocketHandle sock, const std::string& msg) {
    const char* data = msg.c_str();
    int total = 0;
    const int len = static_cast<int>(msg.size());

    while (total < len) {
#ifdef _WIN32
        const int sent = send(sock, data + total, len - total, 0);
#else
        const int sent = static_cast<int>(send(sock, data + total, len - total, 0));
#endif
        if (sent <= 0) {
            return false;
        }
        total += sent;
    }
    return true;
}

inline bool recvLine(SocketHandle sock, std::string& outLine) {
    outLine.clear();
    char c = '\0';

    while (true) {
#ifdef _WIN32
        const int rc = recv(sock, &c, 1, 0);
#else
        const int rc = static_cast<int>(recv(sock, &c, 1, 0));
#endif
        if (rc <= 0) {
            return false;
        }

        if (c == '\n') {
            return true;
        }

        if (c != '\r') {
            outLine.push_back(c);
        }
    }
}

} // namespace net
