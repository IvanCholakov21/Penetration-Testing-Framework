#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace Net {


    bool tcpConnectable(const std::string& ip_address, int port){
        int socket_ = socket(AF_INET, SOCK_STREAM,0);

        if(socket_ < 0){
            return false;
        }
        sockaddr_in target{};
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        inet_pton(AF_INET, ip_address.c_str(), &target.sin_addr);


        int result = connect(socket_, (struct sockaddr*)&target, sizeof(target));

        close(socket_);

        return (result == 0);

    }

    std::string bannerGrab(const std::string& ip_address, int port){
        int socket_ = socket(AF_INET,SOCK_STREAM,0);

        if(socket_ < 0){
            return "";
        }

        sockaddr_in target{};
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        inet_pton(AF_INET, ip_address.c_str(), &target.sin_addr);

        if( connect(socket_, (struct sockaddr*)&target, sizeof(target)) < 0){
            close(socket_);
            return "";
        }

        char buffer[1024];

        int received = recv(socket_,buffer,sizeof(buffer)-1,0);

        close(socket_);

        if(received == 0){
            return "";
        }
        buffer[received] = '\0';
        return std::string(buffer);
    }
}