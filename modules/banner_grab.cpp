#include "core/module.h"
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include "core/network.h"


class banner_grab: public Module {

    std::string name() const override {
        return "Banner_Grabber";
    }

    std::string description() const override {
        return "Grabs service banner from IP:PORT";
    }

    void run(const std::string target_ip) {

        auto pos = target_ip.find(':');
        if(pos == std::string::npos){
            std::cout << "Use format IP:PORT\n";
            return;
        }

        std::string ip_address = target_ip.substr(0,target_ip.find(':'));
        std::string port_as_string = target_ip.substr(target_ip.find(':')+1,target_ip.size()-1);
        uint16_t port = std::stoi(port_as_string);
        if(port < 0 || port > 65535){
            throw std::out_of_range("Invalid value of uint16_t port");
        }

        std::string result = Net::bannerGrab(ip_address,port);

        if(result.empty()){
            std::cout << "No banner received.\n";
        } else {
            std::cout << "Banner:\n" << result << "\n";
        }

    }


};


std::shared_ptr<Module> make_banner_grab(){
    return std::make_shared<banner_grab>();
}