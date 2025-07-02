#ifndef BASIS_3D_HPP
#define BASIS_3D_HPP

#include <string>
#include <stdexcept>
#include <array>
#include <tuple>

#include "Matrix.hpp"
#include "SquareMatrix.hpp"

#include "Logger.hpp"
#include "StringUtils.hpp"
#include "Vector3d.hpp"
#include "Vector2d.hpp"

class Basis3d {
    private:
        SquareMatrix<3> data;
    public:
        Basis3d(const std::array<std::array<double, 3>, 3>& arg_data);
        explicit Basis3d(const Vector3d& x = Vector3d(), const Vector3d& y = Vector3d(), const Vector3d& z = Vector3d());
        explicit Basis3d(const SquareMatrix<3>& sq_matrix);
        explicit Basis3d(); // returns an identity basis

        // copy constructor
        Basis3d(const Basis3d&) = default;
        // move constructor
        Basis3d(Basis3d&&) = default;
        // copy assignment operator
        Basis3d& operator=(const Basis3d&) = default;
        // move assignment operator
        Basis3d& operator=(Basis3d&&) = default;

        void set_basis_xy(const Vector3d& x, const Vector3d& y);
        void set_basis_yz(const Vector3d& y, const Vector3d& z);
        void set_basis_zx(const Vector3d& z, const Vector3d& x);
        void set_basis(const Vector3d& x, const Vector3d& y, const Vector3d& z);
        
        
        inline Vector3d x_axis() const { return Vector3d(data.get_column(0)); }
        inline Vector3d y_axis() const { return Vector3d(data.get_column(1)); }
        inline Vector3d z_axis() const { return Vector3d(data.get_column(2)); }
        inline SquareMatrix<3>& get_matrix() { return data; }
        inline const SquareMatrix<3>& get_matrix() const { return data; }
        std::tuple<Vector3d, Vector3d, Vector3d> get_axes() const;
        Matrix<3, 2> get_xy_matrix() const;
        
        Vector3d local_to_world(const Vector2d& vect) const;
        Vector3d local_to_world(const Vector3d& vect) const;

        void transform(const SquareMatrix<3>& transformer);
        void normalized_transform(const SquareMatrix<3>& transformer);


    private:
        void set_basis_no_check(const Vector3d& x, const Vector3d& y, const Vector3d& z);

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
            
            if (!data.is_size_equal(3, 3)) {
                Logger::log_and_throw<ExceptionType>(
                    "Basis3d::" + func_name + " throw_if_not_3x3", 
                    "size of matrix for basis3d must be 3x3");
                throw;
            }
        }
        template<typename ExceptionType = std::runtime_error>
        inline void throw_if_basis_not_perpendicular(
            std::string func_name
        ) const {
            if (
                !x_axis().is_perpendicular(y_axis()) ||
                !y_axis().is_perpendicular(z_axis()) ||
                !z_axis().is_perpendicular(x_axis())
            ) {
                log_and_throw<ExceptionType>(
                    func_name + " throw_if_basis_not_perpendicular", 
                    "basis has to be perpendicular with each other"
                );
                throw;
            }
        }
        template<typename ExceptionType = std::runtime_error>
        inline void throw_if_not_perpendicular(const Vector3d& x, const Vector3d& y, std::string func_name) const {
            
            if (!x_axis().is_perpendicular(y_axis())) {
                log_and_throw<ExceptionType>(
                    func_name + " throw_if_not_perpendicular", 
                    "vect1:" + x.to_string(false) + " vect2:" + y.to_string(false));
                throw;
            }
        }
        template<typename ExceptionType = std::runtime_error>
        inline void throw_if_not_perpendicular(
            const Vector3d& x, 
            const Vector3d& y, 
            const Vector3d& z, 
            std::string func_name
        ) const {
            if (
                !x_axis().is_perpendicular(y_axis()) ||
                !y_axis().is_perpendicular(z_axis()) ||
                !z_axis().is_perpendicular(x_axis())
            ) {
                log_and_throw<ExceptionType>(
                    func_name + " throw_if_not_perpendicular", 
                    "x:" + x.to_string(false) 
                        + " y:" + y.to_string(false) 
                        + " z:" + z.to_string(false)
                );
                throw;
            }
        }

        template <typename ExceptionType>
        [[noreturn]] inline void log_and_throw(std::string func_name, std::string message) {
            Logger::log_and_throw(
                "Basis3d::" 
                    + func_name,
                message 
                    + "\n(object status)\n  data:" 
                    + StringUtils::add_indent(
                        data.to_string(false), 4, false)
            );
        }

};







#endif // BASIS_3D_HPP