#include "core/module.h"
#include "include/fuzzer.h"
#include "core/logger.h"
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <random>
#include <vector>
#include <thread>
#include <chrono>
#include <core/network.h>



class fuzzer: public Module {

    

    std::string name() const override{
        return "Fuzzer";
    }

    std::string description() const override{
        return "This module throws invalid input and observes the behaviour";
    }

    void run(const std::string target_ip) override{

        auto pos = target_ip.find(':');
        if(pos == std::string::npos){
            Logger::error("Use format IP:PORT\n");
            return;
        }

        Logger::info("Starting Fuzzer on " + target_ip);

        std::string ip_address = target_ip.substr(0,target_ip.find(':'));
        std::string port_as_string = target_ip.substr(target_ip.find(':')+1,target_ip.size()-1);
        
        uint16_t port = std::stoi(port_as_string);
        if(port < 0 || port > 65535){
            throw std::out_of_range("Invalid value of uint16_t port");
        }

        for(int i = 0; i<100;i++){
            auto payload = generate_payload();

            int sock = Net::net_connect(ip_address,port);

            Net::net_send(sock, payload);

            std::string response;
            if(!Net::net_receive(sock,response,2000)){
                Logger::warning("Possible hang detected");
            }

            Net::net_close(sock);

            std::this_thread::sleep_for(std::chrono::milliseconds(50));




        }

        Logger::info("Fuzzing complete");

    }

    private:
    std::vector<uint8_t> generate_payload() {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> len_dist(1,1024);
        std::uniform_int_distribution<int> byte_dist(0,255);

        int len = len_dist(rng);

        std::vector<uint8_t> data(len);

        for(auto& b : data){
            b = static_cast<uint8_t>(byte_dist(rng));
        }
        return data;
    }


};


std::shared_ptr<Module> make_fuzzer(){
    return std::make_shared<fuzzer>();

}