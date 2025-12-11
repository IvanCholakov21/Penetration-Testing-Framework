#pragma once
#include "module.h"
#include <vector>
#include <memory>


class ModuleManager {
    private:
    std::vector<std::shared_ptr<Module>> modules;


    public:

    void registerModule(std::shared_ptr<Module> m){
        modules.push_back(m);
    }

    std::vector<std::shared_ptr<Module>> list() const{
        return modules;

    }

    std::shared_ptr<Module> getModule(std::string module_name) const{

        for(std::shared_ptr<Module> current_module : modules){
            if(current_module->name() == module_name){
                return current_module;
            }

        }
        return nullptr;

    }




};

