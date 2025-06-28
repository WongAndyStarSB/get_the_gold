#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include <array>
#include <vector>
#include <stdexcept>
#include <string>

#include "Logger.hpp"

template <const size_t N>
class SquareMatrix {
    static_assert(N > 0, "Matrix size must be positive");
    public:
        std::array<std::array<double, N>, N> data;
        inline constexpr size_t size() const { return N; }

        inline constexpr SquareMatrix(const std::array<std::array<double, N>, N>& arg_data) 
            : data(arg_data) {
        }
        inline constexpr explicit SquareMatrix(const double& default_val = 0.0) {
            for (auto it = data.begin(); it != data.end(); ++it) {
                for (auto jt = it->begin(); jt != it->end(); ++jt) {
                    (*jt) = default_val;
                }
            }
        }
        inline explicit SquareMatrix(const std::vector<std::vector<double>>& arg_data) {
            assign_with_vector(arg_data);
        }

        inline SquareMatrix(const SquareMatrix<N>&) = default;
        inline SquareMatrix(SquareMatrix<N>&&) = default;

        inline SquareMatrix<N>& operator=(const SquareMatrix<N>& other) {
            if (this == &other) { // self-assignment check
                return *this;  
            }
            data = other;
            return *this;
        }
        inline SquareMatrix<N>& operator=(SquareMatrix<N>&& other) noexcept = default;

        inline SquareMatrix<N>& operator=(const std::array<std::array<double, N>, N>& other) {
            data = other;
            return *this;
        }
        inline SquareMatrix<N>& operator=(const std::vector<std::vector<double>>& arg_data) {
            return assign_with_vector(arg_data);
        }

        inline SquareMatrix<N>& assign_with_vector(const std::vector<std::vector<double>>& arg_data) {
            if (arg_data.size() != N) {
                Logger::log_and_throw<std::invalid_argument>(
                    "SquareMatrix<" + std::to_string(N) + ">::SquareMatrix", 
                    "arg_data must have the same size as N");
            }
            for (auto it = arg_data.cbegin(); it != arg_data.cend(); ++it) {
                if ((*it).size() != N) {
                    Logger::log_and_throw<std::invalid_argument>(
                        "SquareMatrix<" + std::to_string(N) + ">::SquareMatrix", 
                        "all rows of arg_data must have the same size as N");
                }
            }
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    data[r][c] = arg_data[r][c];
                }
            }
            return *this;
        }

        inline bool operator==(const SquareMatrix<N>& other) const {
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    if (data[r][c] != other[r][c]) {
                        return false;
                    }
                }
            }
            return true;
        }
        inline bool operator!=(const SquareMatrix& other) const {
            return !operator==(other);
        }


        inline std::array<double, N>& operator[](size_t index) {
            if (index >= N) {
                Logger::log_and_throw<std::out_of_range>(
                    "SquareMatrix<" + std::to_string(N) + ">::operator[]", 
                    "index(" + std::to_string(index) + ") out of range (0 to N-1)"
                );
            }
            return data[index];
        }
        inline const std::array<double, N>& operator[](size_t index) const {
            if (index >= N) {
                Logger::log_and_throw<std::out_of_range>(
                    "SquareMatrix<" + std::to_string(N) + ">::operator[]", 
                    "(const) index(" + std::to_string(index) + ") out of range (0 to N-1)"
                );
            }
            return data[index];
        }

        inline bool is_size_equal(size_t arg_size) const {
            return arg_size == N;
        }

        inline std::array<double, N> get_column(size_t col_index) const {
            if (col_index >= N) {
                Logger::log_and_throw<std::out_of_range>(
                    "SquareMatrix<" + std::to_string(N) + ">::get_column: ", 
                    "col_index out of range (0 to N-1)"
                );
            }
            std::array<double, N> column;
            for (size_t i = 0; i < N; ++i) {
                column[i] = data[i][col_index];
            }
            return column;
        }

        inline SquareMatrix<N> operator-() const { // negative operator
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = -data[r][c];
                }
            }
            return result;
        }
        inline SquareMatrix<N> operator+(const SquareMatrix<N>& other) const {
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] + other[r][c];
                }
            }
            return result;
        }
        inline SquareMatrix<N> operator-(const SquareMatrix<N>& other) const { // minus operator
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] - other[r][c];
                }
            }
            return result;
        }
        inline SquareMatrix<N> operator*(const SquareMatrix<N>& other) const {
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


        inline SquareMatrix<N> operator*(double scalar) {
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] * scalar;
                }
            }
            return result;
        }
        inline SquareMatrix<N> operator/(double scalar) {
            SquareMatrix<N> result;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result[r][c] = data[r][c] / scalar;
                }
            }
            return result;
        }
        
        inline SquareMatrix<N> transpose() const {
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
                Logger::log_and_throw<std::runtime_error>(
                    "SquareMatrix::inverse", 
                    "Matrix is singular/non-invertible(determinant is zero)");
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
                Logger::log_and_throw<std::logic_error>(
                    "SquareMatrix<1>::matrix_of_minor", 
                    "should not be called when N = 1"
                );
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
                Logger::log_and_throw<std::runtime_error>(
                    "SquareMatrix::<" + std::to_string(N) + ">", 
                    "determinant NEVER 0");
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
                SquareMatrix<N-1> sub_matrix;
                std::array<double, N-1> tmp_arr;
                for (size_t r = 0; r < N-1; ++r) {
                    for (size_t c = 0; c < N-1; ++c) {
                        sub_matrix[r][c] = data[r+1][c+1];
                    }
                }
                for (size_t r = 0; r < N; ++r) {
                    result += ((r % 2 == 1)? -1 : 1) * data[r][0] * sub_matrix.determinant();
                    if (r == N-1) {
                        return result;
                    }
                    
                    // sub_array of data[r] from index 1 to end // data[r][1:]
                    for (size_t i = 0; i < N-1; ++i) {
                        tmp_arr[i] = data[r][i+1];
                    }
                    sub_matrix[r] = tmp_arr;
                }
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

        inline std::string to_string(bool add_prefix = true, size_t decimal_point = 3, std::string elem_sep = ", ", std::string line_sep = "], \n [", std::string front = "[[", std::string end = "]]") {
            std::string result;
            result += (add_prefix? "Matrix(\n" : "(\n") + front;
            for (size_t r = 0; r < N; ++r) {
                for (size_t c = 0; c < N; ++c) {
                    result += 
                        std::to_string(std::round(data[r][c])) 
                        + (c < N-1? elem_sep : "");
                }
                result += (r < N-1? line_sep : end);
            }
            result += "\n)";
            return result;
        }

        

        inline static constexpr SquareMatrix<N> IdentityMatrix() {
            constexpr SquareMatrix<N> I(0);

            for (size_t i = 0; i < N; ++i) {
                I.data[i][i] = 1;
            }
            return I;
        } 

        inline SquareMatrix<N> T() const { return transpose(); }
        inline SquareMatrix<N> Neg1() const { return inverse(); }
        inline static constexpr SquareMatrix<N> I() { return IndentityMatrix(); }
        
};


#endif