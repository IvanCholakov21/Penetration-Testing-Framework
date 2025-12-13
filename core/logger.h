#pragma once
#include <string>
#include <chrono>
#include <mutex>


namespace Logger {

enum class LogLevel {
    ERROR,
    INFO,
    WARNING,
    SUCCESS,
    DEBUG
};

extern bool debugEnabled;
extern bool colorEnabled;
extern std::mutex logMutex;



    
    std::string getColorForLevel(LogLevel level);

    std::string getTimeStamp();

    std::string labelforLevel(LogLevel level);
    void log(LogLevel level, const std::string message);
    void info(const std::string& msg);

    void warning(const std::string& msg);

    void error(const std::string& msg);

    void success(const std::string& msg);

    void debug(const std::string& msg);

    void setDebug(bool enabled);

    void enableColors(bool enabled);
    



}