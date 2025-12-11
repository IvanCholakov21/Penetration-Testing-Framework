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
        return "Banner Grabber";
    }

    std::string description() const override {
        return "Grabs vital informations";
    }

    void run(const std::string target) {

    }





};


std::shared_ptr<Module> make_banner_grab(){
    return std::make_shared<banner_grab>();
}