#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <type_traits>

namespace StringUtils {
    std::string add_indent(
        const std::string& txt, 
        const size_t& indent_num, 
        const char& indent_char = ' '
    ) {
        std::string indent_string (indent_num, indent_char);
        std::string result = indent_string;
        for (char c : txt) {
            result += c;
            if (c == '\n') {
                result += indent_string;
            }
        }
        return result;
    }

    template <typename ExceptionType>
    static std::string common_exceptions_to_string() {
        static_assert(
            std::is_base_of<std::exception, ExceptionType>::value, 
            "type must derive from std::exception"
        );
        if constexpr (std::is_same<ExceptionType, std::runtime_error>::value) {
            return "std::runtime_error";
        } else if constexpr (std::is_same<ExceptionType, std::logic_error>::value) {
            return "std::logic_error";
        } else if constexpr (std::is_same<ExceptionType, std::domain_error>::value) {
            return "std::domain_error";
        } else if constexpr (std::is_same<ExceptionType, std::invalid_argument>::value) {
            return "std::invalid_argument";
        } else if constexpr (std::is_same<ExceptionType, std::out_of_range>::value) {
            return "std::out_of_range";
        } else if constexpr (std::is_same<ExceptionType, std::length_error>::value) {
            return "std::length_error";
        } else if constexpr (std::is_same<ExceptionType, std::runtime_error>::value) {
            return "std::runtime_error";
        } else if constexpr (std::is_same<ExceptionType, std::range_error>::value) {
            return "std::range_error";
        } else if constexpr (std::is_same<ExceptionType, std::overflow_error>::value) {
            return "std::overflow_error";
        } else if constexpr (std::is_same<ExceptionType, std::underflow_error>::value) {
            return "std::underflow_error";
        } else {
            return "unknown_exception(" + ExceptionType().what() + ")";
        }
    }

}
    


#endif // STRING_UTILS_HPP