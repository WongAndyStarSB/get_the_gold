#ifndef UTILS_HPP
#define UTILS_HPP


#include <string>
#include <cmath>
#include <stdexcept>


namespace Utils {
    inline bool double_equal(double a, double b, double precision = 1e-6) {
        return std::abs(a-b) < precision;
    }
}






#endif // UTILS_HPP