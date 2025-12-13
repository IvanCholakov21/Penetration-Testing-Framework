#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include "core/network.h"
#include "core/module.h"
class port_scanner: public Module {

    std::string name() const override {
        return "Port_Scanner";
    }
    std::string description() const override{
        return "This module scans for a specific port";
    }

    void run(const std::string target_ip) override {

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

        bool open = Net::tcpConnectable(ip_address,port);
        std::cout << "Port" << port << " on " << ip_address << (open ? " is opened" : " is closed");
    }


};


std::shared_ptr<Module> make_scan_port(){
    return std::make_shared<port_scanner>();
}