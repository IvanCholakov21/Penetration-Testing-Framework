#include <string>
#include <sstream>
#include <chrono>
#include <core/logger.h>
#include <iomanip>
#include <mutex>
#include <iostream>


namespace Logger{


bool debugEnabled = false;
bool colorEnabled = true;
std::mutex logMutex;

    
    std::string getColorForLevel(LogLevel level){
        if(!colorEnabled) return "";
        switch (level){
        case Logger::LogLevel::ERROR:
        return "\033[31m";

        case Logger::LogLevel::INFO:
        return "\033[36m";

        case Logger::LogLevel::WARNING:
        return "\033[33m";

        case Logger::LogLevel::SUCCESS:
        return "\033[32m";

        case Logger::LogLevel::DEBUG:
        return "\033[37m";
        
        default: return "";
        }
    }

    std::string labelforLevel(LogLevel level){
        switch(level){
            case Logger::LogLevel::INFO:
            return "INFO";
            case Logger::LogLevel::DEBUG:
            return "DEBUG";
            case Logger::LogLevel::ERROR:
            return "ERROR";
            case Logger::LogLevel::SUCCESS:
            return "SUCCESS";
            case Logger::LogLevel::WARNING:
            return "WARNING";
            default: 
            return "LOG";
        }
    }


    std::string getTimeStamp(){
        using clock = std::chrono::system_clock;
        auto time = clock::to_time_t(clock::now());
        std::ostringstream oss;
        
        
        std::tm tm{};
    #if defined(_WIN32)
            localtime_s(&tm, &time);
        
    #else 
            localtime_r(&time,&tm);
        
    #endif


    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
    
    


    }

    void log(LogLevel level, std::string message){
        if(level == LogLevel::DEBUG && !debugEnabled){
            return;
        }

        std::lock_guard<std::mutex> lock(logMutex);

        const std::string color = getColorForLevel(level);

        std::cout 
        << "[" << getTimeStamp() << "] "
        << color
        << "[" << labelforLevel(level) << "] "
        << "\033[0m"
        << message
        << std::endl;
    }
    void info(const std::string& msg) {
    log(LogLevel::INFO, msg);
    }  

    void warning(const std::string& msg) {
    log(LogLevel::WARNING, msg);
    }

    void error(const std::string& msg) {
    log(LogLevel::ERROR, msg);
    }

    void success(const std::string& msg) {
    log(LogLevel::SUCCESS, msg);
    }

    void debug(const std::string& msg) {
    log(LogLevel::DEBUG, msg);
    }

    void setDebug(bool enabled) {
    debugEnabled = enabled;
    }

    void enableColors(bool enabled) {
    colorEnabled = enabled;
    }



}