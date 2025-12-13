#include <iostream>
#include "core/module_manager.h"
#include "core/logger.h"

std::shared_ptr<Module> make_banner_grab();
std::shared_ptr<Module> make_scan_port();

int main(){

    ModuleManager manager;


    manager.registerModule(make_scan_port());
    manager.registerModule(make_banner_grab());

    std::cout << "Pentest Framework\n";
    std::cout << "Type list to see modules";

    std::string cmd;
    while(true){
        std::cout << "> ";
        std::getline(std::cin, cmd);

        if(cmd == "exit"){
            break;
        }

        if(cmd == "list"){

            for(auto& module : manager.list()){
                std::cout << module->name() << " - " << module->description() << "\n";
                
            }
            continue;
        }

        auto space = cmd.find(' ');

        if(space == std::string::npos){
            Logger::warning("Please follow the format: <module> <target>"); 
            
            continue;
        }


        std::string module_Name = cmd.substr(0,cmd.find(' '));
        std::string target_ip = cmd.substr(cmd.find(' '), cmd.size());

        auto mod = manager.getModule(module_Name);

        if(!mod){
            Logger::error("Unknown or not implemented module");
            continue;
        }

        mod->run(target_ip);

    }





    return 0;
}