#ifndef BASIS_3D_HPP
#define BASIS_3D_HPP

#include <stdexcept>

#include "Matrix.hpp"
#include "Vector3d.hpp"
#include "Vector2d.hpp"

class Basis3d : public Matrix {
    
    public:
        explicit Basis3d(const std::vector<std::vector<double>>& arg_data);
        explicit Basis3d(size_t arg_num_of_row, size_t arg_num_of_col, double default_val = 0.0);
        inline Vector3d x_axis() const { return get_column(0); }
        inline Vector3d y_axis() const { return get_column(1); }
        inline Vector3d z_axis() const { return get_column(2); }
        Vector3d local_to_world(const Vector2d& vect) const;
        Vector3d local_to_world(const Vector3d& vect) const;

    private:
        /**
         * @brief Throws an exception if the matrix is not 3x3.
         * 
         * This function checks whether the current matrix has a size of 3x3.
         * If not, it throws an exception of the specified type (default: std::runtime_error)
         * with a fixed error message. The exception type must derive from std::exception.
         * 
         * @tparam ExceptionType The type of exception to throw (must derive from std::exception).
         *                       Defaults to std::runtime_error.
         * 
         * @throws ExceptionType if the matrix is not 3x3.
         */
        template<typename ExceptionType = std::runtime_error>
        void throw_if_not_3x3() const {
            static_assert(
                std::is_base_of<std::exception, ExceptionType>::value, 
                "ExceptionType must derive from std::exception"
            );
            if (!is_size_equal(3, 3)) {
                throw std::ExceptionType("Basis3d::throw_if_invalid_size InvalidArg: size of matrix for basis3d must be 3x3");
            }
        }
};







#endif // BASIS_3D_HPP