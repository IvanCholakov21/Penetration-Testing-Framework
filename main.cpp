#include <iostream>
#include "core/module_manager.h"
#include "core/logger.h"

std::shared_ptr<Module> make_banner_grab();
std::shared_ptr<Module> make_scan_port();
std::shared_ptr<Module> make_fuzzer();

int main(){

    ModuleManager manager;


    manager.registerModule(make_scan_port());
    manager.registerModule(make_banner_grab());
    manager.registerModule(make_fuzzer());

    std::cout << " __________________________________________________________________________________________________\n";
    std::cout << "|                                                                                                  |\n";
    std::cout << "|    _________   ________   _               _   ____________   ________   ________   ____________  |\n";
    std::cout << "|   ||       || ||_______| | |\\            | | |____________| ||_______| |________| |____________| |\n";
    std::cout << "|   ||       || ||         | |  \\          | |       ||       ||         ||               ||       |\n";
    std::cout << "|   ||_______|| ||_______  | |    \\        | |       ||       ||_______  ||_______        ||       |\n";
    std::cout << "|   ||          ||_______| | |      \\      | |       ||       ||_______| ||______|        ||       |\n";
    std::cout << "|   ||          ||         | |        \\    | |       ||       ||                 ||       ||       |\n";
    std::cout << "|   ||          ||_______  | |          \\  | |       ||       ||_______   _______||       ||       |\n";
    std::cout << "|   ||          ||_______| |_|            \\|_|       ||       ||_______| |_______||       ||       |\n";
    std::cout << "|                                                                                                  |\n";
    std::cout << "|                                                                                                  |\n";
    std::cout << "|__________________________________________________________________________________________________|\n";
    std::cout << "Pentest Framework\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Commands:\n";
    std::cout << "> list - list all available modules\n";

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