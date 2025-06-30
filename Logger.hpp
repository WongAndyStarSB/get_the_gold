#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <stdexcept>
#include <type_traits>




namespace Logger {

    enum LogLevel {
        INFO,
        WARNING_1,
        WARNING_2,
        WARNING_3,
        ERROR,
        DEBUG
    };

    class SeeAbove : public std::exception {
        std::string msg_;
        public:
            inline explicit SeeAbove(
                const std::string& message
            ) : msg_("<SeeAbove> " + message) {}

            inline const char* what() const noexcept override {
                return msg_.c_str();
            }
    };
    

    void log(const std::string& func_name, const std::string& message, LogLevel lev, bool add_timestamp = true);
    
    void start_run(const std::string& message = "");

    template <typename ExceptionType = std::runtime_error>
    [[noreturn]] void log_and_throw(const std::string& where, const std::string& message);

} // namespace Logger

#include "Logger.inl" // For template implementation

#endif // LOGGER_HPP