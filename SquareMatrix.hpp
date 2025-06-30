#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "Matrix.hpp"

#include <array>
#include <vector>
#include <stdexcept>
#include <string>

#include "Logger.hpp"

template <const size_t N>
class SquareMatrix : public Matrix<N, N> {
    static_assert(N > 0, "SquareMatrix: N(size) must be positive");

    public:
        using Matrix<N, N>::data;

        inline constexpr SquareMatrix(
            const std::array<std::array<double, N>, N>& arg_data
        ) noexcept
         : Matrix<N, N>(arg_data) {
        }
        inline constexpr explicit SquareMatrix(
            const double& default_val = 0.0
        ) noexcept
         : Matrix<N, N>(default_val) {
        }
        inline explicit SquareMatrix(
            const std::vector<std::vector<double>>& arg_data
        ) noexcept
         : Matrix<N, N>(arg_data) {
        }

        // copy constructor
        inline SquareMatrix(const SquareMatrix<N>& other) = default;
        // move constructor
        inline SquareMatrix(SquareMatrix<N>&& other) noexcept = default;

        // assignment operator
        inline SquareMatrix<N>& operator=(const SquareMatrix<N>& other) {
            if (this == &other) { // self-assignment check
                return *this;
            }
            return this->Matrix<N, N>::operator=(other);
        }
        // move assignment operator
        inline SquareMatrix<N>& operator=(SquareMatrix<N>&& other) noexcept = default;
        // array assignment operator
        inline SquareMatrix<N>& operator=(const std::array<std::array<double, N>, N>& arg_data) {
            return this->Matrix<N, N>::operator=(arg_data);
        }
        // vector assignment operator
        inline SquareMatrix<N>& operator=(const std::vector<std::vector<double>>& arg_data) {
            try {
                return this->Matrix<N, N>::operator=(arg_data);
            } catch (const std::exception& e) {
                log_and_throw<Logger::SeeAbove>(
                    "operator=(const std::vector<std::vector<double>>& arg_data)",
                    e.what()
                );
                throw;
            }
        }

        inline bool operator==(const SquareMatrix<N>& other) const {
            return Matrix<N, N>::operator==(other);
        }
        inline bool operator!=(const SquareMatrix<N>& other) const {
            return !operator==(other);
        }


        inline std::array<double, N>& operator[](size_t index) {
            try {
                return Matrix<N, N>::operator[](index);
            } catch (const std::exception& e) {
                log_and_throw<Logger::SeeAbove>(
                    "operator[](size_t index)", 
                    e.what()
                );
                throw;
            }
        }
        inline const std::array<double, N>& operator[](size_t index) const {
            try {
                return Matrix<N, N>::operator[](index);
            } catch (const std::exception& e) {
                log_and_throw<Logger::SeeAbove>(
                    "operator[](size_t index) const",
                    e.what()
                );
                throw;
            }
        }

        inline constexpr bool is_size_equal(size_t arg_size) const noexcept {
            return arg_size == N;
        }

        inline std::array<double, N> get_column(size_t col_index) const {
            try {
                return Matrix<N, N>::get_column(col_index);
            } 
            catch (const std::exception& e) {
                log_and_throw<Logger::SeeAbove>(
                    "get_column(size_t col_index)", 
                    e.what()
                );
                throw;
            }
        }

        inline constexpr SquareMatrix<N> operator-() const noexcept { // negative operator
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = -data[r][c];
                }
            }
            return result;
        }
        inline constexpr SquareMatrix<N> operator+(const SquareMatrix<N>& other) const noexcept {
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] + other[r][c];
                }
            }
            return result;
        }
        inline constexpr SquareMatrix<N> operator-(const SquareMatrix<N>& other) const noexcept { // minus operator
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] - other[r][c];
                }
            }
            return result;
        }
        inline constexpr SquareMatrix<N> operator*(const SquareMatrix<N>& other) const noexcept {
            SquareMatrix<N> result;
            double tmp;
            for (size_t rr = 0; rr < N; ++rr) {
                for (size_t rc = 0; rc < N; ++rc) {
                    tmp = 0;
                    for (size_t i = 0; i < N; ++i) {
                        tmp += data[rr][i] * other[i][rc];
                    }
                    result[rr][rc] = tmp;
                }
            }
            return result;
        }
        // inline SquareMatrix<N> operator*(const SquareMatrix<N> other) const {}

        inline constexpr SquareMatrix<N> operator*(double scalar) const noexcept {
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] * scalar;
                }
            }
            return result;
        }
        inline SquareMatrix<N> operator/(double scalar) const {
            if (scalar == 0) {
                log_and_throw<std::domain_error>(
                    "operator/(double scalar) const", 
                    "scalar cannot be 0. attempts to do ZeroDivision.");
                throw;
            }
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] / scalar;
                }
            }
            return result;
        }
        
        inline SquareMatrix<N>& operator+=(const SquareMatrix<N>& other) noexcept {
            for (size_t r = 0; r < N; ++r)
                for (size_t c = 0; c < N; ++c)
                    data[r][c] += other[r][c];
            return *this;
        }
        inline SquareMatrix<N>& operator-=(const SquareMatrix<N>& other) noexcept {
            for (size_t r = 0; r < N; ++r)
                for (size_t c = 0; c < N; ++c)
                    data[r][c] -= other[r][c];
            return *this;
        }
        inline SquareMatrix<N>& operator*=(const SquareMatrix<N>& other) noexcept {
            data = operator*(other).data;
            return *this;
        }
        
        inline SquareMatrix<N>& operator*=(double scalar) {
            for (size_t r = 0; r < N; ++r)
                for (size_t c = 0; c < N; ++c)
                    data[r][c] *= scalar;
            return *this;
        }
        inline SquareMatrix<N>& operator/=(double scalar) {
            if (scalar == 0) {
                log_and_throw<std::domain_error>(
                    "operator/=(double scalar)", 
                    "scalar cannot be 0. attempts to do ZeroDivision.");
                throw;
            }
            for (size_t r = 0; r < N; ++r)
                for (size_t c = 0; c < N; ++c)
                    data[r][c] /= scalar;
            return *this;
        }

        inline constexpr SquareMatrix<N> transpose() const noexcept {
            if (N == 1) {
                return SquareMatrix<1>(data[0][0]);
            }
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) { 
                    result[r][c] = data[c][r];
                }
            }
            return result;
        }
        inline SquareMatrix<N> inverse() const {
            double det = determinant();
            if (det == 0) {
                log_and_throw<std::runtime_error>(
                    "inverse() const", 
                    "this SquareMatrix is singular/non-invertible(determinant is zero)");
                throw;
            }
            if constexpr (N==1) {
                return SquareMatrix<1>(1/data[0][0]);
            } else if constexpr (N==2) {
                return (
                    SquareMatrix<2>({
                        {data[1][1], -data[0][1]}, 
                        {-data[1][0], data[0][0]}
                    }) / det
                );
            } else {
                SquareMatrix<N> tmp;
                for (size_t r = 0; r < N; ++r) {
                    for (size_t c = 0; c < N; ++c) {
                        tmp[r][c] = this->cofactor(r, c);
                    }
                }
                return tmp.transpose() / det;
            }
        }

        inline SquareMatrix<N-1> matrix_of_minor(size_t row, size_t col) const {
            if constexpr (N==1) {
                log_and_throw<std::logic_error>(
                    "matrix_of_minor(size_t row, size_t col) const", 
                    "should not be called when N = 1"
                );
                throw;
            } else {
                SquareMatrix<N-1> minor;
                for (size_t mr = 0; mr < N-1; ++mr) {
                    for (size_t mc = 0; mc < N-1; ++mc) {
                        minor[mr][mc] = 
                            data[ (row < mr)? mr : mr+1 ][ (col < mc)? mc : mc+1 ]
                        ;
                    }
                }
                return minor;
            }
        }
        inline double minor(size_t row, size_t col) const {
            if constexpr (N == 1) {
                return data[0][0];
            } else {
                return matrix_of_minor(row, col).determinant();
            }
        }
        inline double cofactor(size_t row, size_t col) const {
            return ( ((row + col) % 2 == 0) ? 1 : -1 ) * minor(row, col);
        }
        
        inline double determinant() const {
            if constexpr (N == 0) {
                log_and_throw<std::runtime_error>(
                    "determinant() const", 
                    "determinant NEVER 0");
                throw;
            }
            else if constexpr (N == 1) {
                return data[0][0];
            }
            else if constexpr (N == 2) {
                return data[0][0] * data[1][1] - data[0][1] * data[1][0];
            }
            else if constexpr (N == 3) {
                return
                      data[0][0] * data[1][1] * data[2][2]
                    + data[0][1] * data[1][2] * data[2][0]
                    + data[0][2] * data[1][0] * data[2][1]
                    - data[0][2] * data[1][1] * data[2][0]
                    - data[0][1] * data[1][0] * data[2][2]
                    - data[0][0] * data[1][2] * data[2][1];
            } else {
                static_assert(N > 3, "SquareMatrix::determinant NEVER !>3");
                // N > 3
                // with minor() {
                // double result = 0.0;
                // for (size_t r = 0; r < N; ++r) {
                //     result += ((r % 2 == 1)? -1 : 1) * data[r][0] * minor(r, 0).determinant();
                // }
                // } mine {
                double result = 0;
                SquareMatrix<N-1> minor_matrix;
                std::array<double, N-1> tmp_arr;
                for (size_t r = 0; r < N-1; ++r) {
                    for (size_t c = 0; c < N-1; ++c) {
                        minor_matrix[r][c] = data[r+1][c+1];
                    }
                }
                for (size_t r = 0; r < N; ++r) {
                    result += ((r % 2 == 1)? -1 : 1) * data[r][0] * minor_matrix.determinant();
                    if (r == N-1) {
                        return result;
                    }
                    
                    // sub_array of data[r] from index 1 to end // data[r][1:]
                    for (size_t i = 0; i < N-1; ++i) {
                        tmp_arr[i] = data[r][i+1];
                    }
                    minor_matrix[r] = tmp_arr;
                }
                log_and_throw<std::runtime_error>(
                        "determinant() const",
                        "UNREACHEABLE"
                );
                throw;
                // } AI {
                // double result = 0.0;
                // for (size_t col = 0; col < N; ++col) {
                //     SquareMatrix<N-1> minor;
                //     // Build the minor matrix by skipping row 0 and column 'col'
                //     for (size_t i = 1; i < N; ++i) {
                //         size_t minor_col = 0;
                //         for (size_t j = 0; j < N; ++j) {
                //             if (j == col) continue;
                //             minor[i-1][minor_col] = data[i][j];
                //             ++minor_col;
                //         }
                //     }
                //     double sign = ((col % 2) == 0) ? 1.0 : -1.0;
                //     result += sign * data[0][col] * minor.determinant();
                // }
                // return result;
                // }
            }
        }

        inline std::string to_string(
            bool add_prefix = true, 
            std::string elem_sep = ", ", 
            std::string line_sep = "], \n [", 
            std::string front = "[[", 
            std::string end = "]]"
        ) const {
            return 
                (add_prefix? "SquareMatrix<" + std::to_string(N) + ">" : "") 
                + Matrix<N, N>::to_string(false, elem_sep, line_sep, front, end)
            ;
        }

        

        inline static constexpr SquareMatrix<N> IdentityMatrix() noexcept {
            SquareMatrix<N> I(0);

            for (size_t i = 0; i < N; ++i) {
                I.data[i][i] = 1;
            }
            return I;
        } 
        inline static constexpr SquareMatrix<N> ZeroMatrix() noexcept {
            return SquareMatrix<N>(0);
        }

        inline SquareMatrix<N> T() const { return transpose(); }
        inline SquareMatrix<N> Neg1() const { return inverse(); }
        inline double det() const { return determinant(); }
        inline static constexpr SquareMatrix<N> I() noexcept { return IdentityMatrix(); }
        inline static constexpr SquareMatrix<N> O() noexcept { return SquareMatrix<N>(0); }
        
    private:

        inline void log(const std::string& func_name, const std::string& message, const Logger::LogLevel& log_level, bool add_timestamp) const {
            Logger::log(
                "SquareMatrix<" + std::to_string(N) + ">::" + func_name, 
                message, 
                log_level, 
                add_timestamp
            );
        }

        template <typename ExceptionType = std::runtime_error>
        [[noreturn]] inline void log_and_throw(const std::string& func_name, const std::string& message) const {
            Logger::log_and_throw<ExceptionType>(
                "SquareMatrix<" + std::to_string(N) + ">::" + func_name, 
                message);
        }
};


#endif