#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

#include "StringUtils.hpp"

#define _NORETURN [[noreturn]]

enum LogLevel {
    INFO,
    WARNING_1,
    WARNING_2,
    WARNING_3,
    ERROR,
    DEBUG
};
class Logger {
  private:
    static void log_to_file(const std::string& file_name, const std::string& message) {
        namespace fs = std::filesystem;
        fs::path log_path = "logs/" + file_name + ".log";
        fs::create_directories(log_path.parent_path()); // Ensure directory exists
        
        std::ofstream log_file(log_path, std::ios_base::app);
        if (log_file.is_open()) {
            log_file << message << std::endl;
        } else {
            std::cerr << "Unable to open log file." << std::endl;
        }
        log_file.flush();
    }
    static std::string log_level_to_string(LogLevel lev) {
        switch (lev) {
            case INFO: return "INFO"; break;
            case WARNING_1: return "WARNING_1";
            case WARNING_2: return "WARNING_2";
            case WARNING_3: return "*WARNING_3";
            case ERROR: return "***ERROR";
            case DEBUG: return "debug";
            default: return "UNKNOWN";
        }
    }
    
  public:
    static void log(const std::string& func_name, const std::string& message, LogLevel lev, bool add_timestamp = true) {
        std::string msg = StringUtils::add_indent(func_name + "\n" + message, 4);
    
        std::time_t now = std::time(nullptr);
        std::tm local_time;
        #ifdef _MSC_VER
            localtime_s(&local_time, &now); // MSVC safe version
        #else
            local_time = *std::localtime(&now); // Standard C++ version (not thread-safe)
        #endif
        //'localtime': This function or variable may be unsafe. Consider using localtime_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details. [E:\coding\andy_coding_c\_snake\build\snake-Windows.vcxproj]MSVC(C4996)
        std::string year_str = std::to_string(local_time.tm_year + 1900);
        std::string month_and_day = std::to_string(local_time.tm_mon + 1) + "-" +
                                std::to_string(local_time.tm_mday)
        ;
        if (add_timestamp) {
            std::string timestamp = std::to_string(local_time.tm_hour) + ":" +
                                    std::to_string(local_time.tm_min) + ":" +
                                    std::to_string(local_time.tm_sec)
            ;
            msg = "[" + timestamp + "] [" + log_level_to_string(lev) + "] {\n" + msg + "\n}";
        } else {
            msg = "[] [" + log_level_to_string(lev) + "] {\n" + msg + "\n}";
        }
        log_to_file(year_str + "/" + month_and_day, msg);
    }
    static void start_run(const std::string& message = "") {
        log(
            "",
            std::string(20, '-') +
                " << program started to run >> " +
                std::string(50, '-') + 
                ((message=="")? ("") : ("\n"+StringUtils::add_indent(message, 2))), 
            INFO
        );
    }
    template <typename ExceptionType = std::runtime_error>
    _NORETURN static void log_and_throw(const std::string& func_name, const std::string& message) {
        static_assert(
                std::is_base_of<std::exception, ExceptionType>::value, 
                "type must derive from std::exception"
            );
            std::string msg = 
                "[ERROR] " + StringUtils::common_exceptions_to_string<ExceptionType>()
                + "\n" + message;
            
        log(func_name, msg, ERROR, true);
        throw ExceptionType(message);
    }
};

#endif // LOGGER_HPP
// End of file