
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <core/logger.h>
#include <vector>
#include <cstring>
#include <poll.h>


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

    void net_close(int sockfd){
        if(sockfd >= 0){
            shutdown(sockfd, SHUT_RDWR);
            close(sockfd);
        }
    }


    int net_connect(const std::string& ip_address, int port){
        int sockfd = socket(AF_INET, SOCK_STREAM,0);

        if(sockfd < 0){
            Logger::error("Socket creation failed");
            return -1;
        }

        sockaddr_in target{};
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        inet_pton(AF_INET, ip_address.c_str(), &target.sin_addr);

        if(::connect(sockfd, (sockaddr*)&target, sizeof(target))<0){
            Logger::error("Connection failed");
            net_close(sockfd);
            return -1;
        }

        return sockfd;

    }

    bool net_send(int sockfd,const std::vector<uint8_t>& data){
        size_t sent_total = 0;

        while(sent_total < data.size()){
            ssize_t sent = ::send(sockfd, data.data() + sent_total, data.size() - sent_total,0);
        
            if(sent <= 0){
                Logger::error("Send failed");
                return false;
            }

            sent_total += sent;
        }

        return true;
    }

    bool net_receive(int sockfd, std::string& out, int timeout_ms){
        pollfd pfd{};
        pfd.fd = sockfd;
        pfd.events = POLLIN;

        if(poll(&pfd, 1 ,timeout_ms) <= 0){
            Logger::error("timeout or error");
            return false;
        }

        char buffer[4096];
        ssize_t bytes = recv(sockfd, buffer, sizeof(buffer)-1,0);
        if(bytes <= 0){
            return false;
        }

        buffer[bytes] = '\0';
        out.assign(buffer,bytes);
        return true;
    }

    
}