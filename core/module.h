#pragma once
#include <string>


class Module {

    public:

    virtual ~Module() = default;

    virtual std::string name() const = 0;

    virtual std::string description() const = 0;

    virtual void run(const std::string target) = 0;

};