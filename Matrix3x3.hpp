#ifndef MATRIX_3X3_HPP
#define MATRIX_3X3_HPP

#include <array>
#include "Matrix.hpp"

class Matrix3x3 {
    public:
        std::array<std::array<double, 3>, 3> data;
        const size_t num_of_row = 3;
        const size_t num_of_col = 3;
        
};


#endif