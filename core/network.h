#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace Net{

    bool tcpConnectable(const std::string& ip_address, int port);

    std::string bannerGrab(const std::string& ip_address, int port);

    int net_connect(const std::string& ip_address, int port);

    bool net_send(int sockfd,const std::vector<uint8_t>& data);

    bool net_receive(int sockfd, std::string& out, int timeout_ms);

    void net_close(int sockfd);


}