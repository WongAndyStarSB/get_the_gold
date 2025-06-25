#ifndef BASIS_3D_HPP
#define BASIS_3D_HPP

#include <string>
#include <stdexcept>

#include "Matrix.hpp"
#include "Vector3d.hpp"
#include "Vector2d.hpp"

class Basis3d : public Matrix {
    
    public:
        explicit Basis3d(const std::vector<std::vector<double>>& arg_data);
        explicit Basis3d(const Vector3d& x = Vector3d(), const Vector3d& y = Vector3d(), const Vector3d& z = Vector3d());
        explicit Basis3d(); // returns an identity basis

        void set_basis_xy(const Vector3d& x, const Vector3d& y);
        void set_basis_yz(const Vector3d& y, const Vector3d& z);
        void set_basis_zx(const Vector3d& z, const Vector3d& x);
        void set_basis(const Vector3d& x, const Vector3d& y, const Vector3d& z);

        
        inline Vector3d x_axis() const { return get_column(0); }
        inline Vector3d y_axis() const { return get_column(1); }
        inline Vector3d z_axis() const { return get_column(2); }
        Vector3d local_to_world(const Vector2d& vect) const;
        Vector3d local_to_world(const Vector3d& vect) const;

        


    private:
        void set_basis_no_check(const Vector3d& x, const Vector3d& y, const Vector3d& z);
        template<typename T>
        inline void assert_type_is_exception() const {
            static_assert(
                std::is_base_of<std::exception, T>::value, 
                "type must derive from std::exception"
            );
        }
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
        inline void throw_if_not_3x3(std::string func_name) const {
            assert_type_is_exception<ExceptionType>();
            if (!is_size_equal(3, 3)) {
                throw ExceptionType("Basis3d::" + func_name + " throw_if_not_3x3: size of matrix for basis3d must be 3x3");
            }
        }
        template<typename ExceptionType = std::runtime_error>
        inline void throw_if_basis_not_perpendicular(std::string func_name) const {
            assert_type_is_exception<ExceptionType>();
            if (
                !x_axis().is_perpendicular(y_axis()) ||
                !y_axis().is_perpendicular(z_axis()) ||
                !z_axis().is_perpendicular(x_axis())
            ) {
                throw ExceptionType(
                    "Basis3d::" + func_name 
                    + " throw_if_basis_not_perpendicular: basis has to be perpendicular with each other"
                );
            }
        }
        template<typename ExceptionType = std::runtime_error>
        inline void throw_if_not_perpendicular(const Vector3d& x, const Vector3d& y, std::string func_name) const {
            assert_type_is_exception<ExceptionType>();
            if (!x_axis().is_perpendicular(y_axis())) {
                throw ExceptionType(
                    "Basis::" + func_name + " throw_if_not_perpendicular vect1:"
                    + x.to_string(false) + " vect2:" + y.to_string(false));
            }
        }
        template<typename ExceptionType = std::runtime_error>
        inline void throw_if_not_perpendicular(const Vector3d& x, const Vector3d& y, const Vector3d& z, std::string func_name) const {
            assert_type_is_exception<ExceptionType>();
            if (
                !x_axis().is_perpendicular(y_axis()) ||
                !y_axis().is_perpendicular(z_axis()) ||
                !z_axis().is_perpendicular(x_axis())
            ) {
                throw ExceptionType(
                    "Basis3d::" + func_name 
                    + " throw_if_not_perpendicular: x:" + x.to_string(false) 
                    + " y:" + y.to_string(false) + " z:" + z.to_string(false)
                );
            }
        }
};







#endif // BASIS_3D_HPP