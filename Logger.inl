#ifndef LOGGER_INL
#define LOGGER_INL


#include <type_traits>
#include "StringUtils.hpp"

namespace Logger {

template <typename ExceptionType>
[[noreturn]] void log_and_throw(const std::string& where, const std::string& message) {
    static_assert(
        std::is_base_of<std::exception, ExceptionType>::value,
        "type must derive from std::exception"
    );
    std::string msg =
        "[ERROR] " 
        + ((std::is_same(ExceptionType, see_above))? 
            "see above" : 
            StringUtils::common_exceptions_to_string<ExceptionType>())
        + "\n" + message;

    log(where, msg, ERROR, true);
    throw ExceptionType(message);
}

} // namespace Logger


#endif // LOGGER_INL