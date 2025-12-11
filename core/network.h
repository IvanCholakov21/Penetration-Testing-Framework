#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace Net{

    bool tcpConnectable(const std::string& ip_address, int port);

    std::string bannerGrab(const std::string& ip_address, int port);
}