#include "Logger.hpp"
#include "StringUtils.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <string>

namespace {

using namespace Logger;
// Private helper: log to file
void log_to_file(const std::string& file_name, const std::string& message) {
    namespace fs = std::filesystem;
    fs::path log_path = "logs/" + file_name + ".log";
    fs::create_directories(log_path.parent_path());
    std::ofstream log_file(log_path, std::ios_base::app);
    if (log_file.is_open()) {
        log_file << message << std::endl;
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    log_file.flush();
}
// Private helper: log level to string
std::string log_level_to_string(LogLevel lev) {
    switch (lev) {
        case INFO: return "INFO";
        case WARNING_1: return "WARNING_1";
        case WARNING_2: return "WARNING_2";
        case WARNING_3: return "*WARNING_3";
        case ERROR: return "***ERROR***";
        case DEBUG: return "debug";
        default: return "UNKNOWN";
    }
}

} // end anonymous namespace

namespace Logger {

void log(const std::string& func_name, const std::string& message, LogLevel lev, bool add_timestamp) {

    std::string msg = StringUtils::add_indent(func_name + "\n" + message, 4);

    std::time_t now = std::time(nullptr);
    std::tm local_time;
    #ifdef _MSC_VER
        localtime_s(&local_time, &now);
    #else
        local_time = *std::localtime(&now);
    #endif
    std::string year_str = std::to_string(local_time.tm_year + 1900);
    std::string month_and_day = std::to_string(local_time.tm_mon + 1) + "-" +
                                std::to_string(local_time.tm_mday);
    if (add_timestamp) {
        std::string timestamp = std::to_string(local_time.tm_hour) + ":" +
                                std::to_string(local_time.tm_min) + ":" +
                                std::to_string(local_time.tm_sec);
        msg = "[" + timestamp + "] [" + log_level_to_string(lev) + "] {\n" + msg + "\n}";
    } else {
        msg = "[] [" + log_level_to_string(lev) + "] {\n" + msg + "\n}";
    }
    log_to_file(year_str + "/" + month_and_day, msg);
}

void start_run(const std::string& message) {
    log(
        "",
        std::string(20, '-')
            + " << program started to run >> "
            + std::string(50, '-')
            + ((message == "") ? ("") : ("\n" + StringUtils::add_indent(message, 2))),
        INFO,
        true
    );
}

} // namespace Logger