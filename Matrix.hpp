#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <string>

#include "Logger.hpp"


template <size_t RowN, size_t ColN>
class Matrix { // fixed sized Matrix with elem type using double
    
    static_assert(RowN > 0, "Matrix: RowN cannot be 0");
    static_assert(ColN > 0, "Matrix: ColN cannot be 0");

    public:
        std::array<std::array<double, ColN>, RowN> data;
        
        inline constexpr std::pair<size_t, size_t> size() const { return std::make_pair(RowN, ColN); }
        inline constexpr size_t num_of_row() const { return RowN; }
        inline constexpr size_t num_of_col() const { return ColN; }

        inline constexpr Matrix(
            const std::array<std::array<double, ColN>, RowN>& arg_data
        ) : data(arg_data) {
        }
        inline constexpr explicit Matrix(
            const double& default_val = 0.0
        ) {
            for (auto it = data.begin(); it != data.end(); ++it) {
                for (auto jt = it->begin(); jt != it->end(); ++jt) {
                    (*jt) = default_val;
                }
            }
        }
        inline explicit Matrix(
            const std::vector<std::vector<double>>& arg_data
        ) {
            try {
                assign_with_vector(arg_data);
            } catch (std::exception& e) {
                log_and_throw<Logger::SeeAbove>("Matrix", e.what());
            }
        }

        inline Matrix(const Matrix<RowN, ColN>&) = default;
        inline Matrix(Matrix<RowN, ColN>&&) noexcept = default;

        inline Matrix<RowN, ColN>& operator=(const Matrix<RowN, ColN>& other) {
            if (this == &other) { // self-assignment check
                return *this;  
            }
            data = other.data;
            return *this;
        }
        inline Matrix<RowN, ColN>& operator=(Matrix<RowN, ColN>&& other) noexcept = default;

        inline Matrix<RowN, ColN>& operator=(const std::array<std::array<double, ColN>, RowN>& other) {
            data = other;
            return *this;
        }
        inline Matrix<RowN, ColN>& operator=(const std::vector<std::vector<double>>& arg_data) {
            try {
                return assign_with_vector(arg_data);
            } catch (std::invalid_argument& e) {
                log_and_throw<Logger::SeeAbove>(
                    "operator=", e.what());
                throw;
            }
        }


        inline Matrix<RowN, ColN>& assign_with_vector(const std::vector<std::vector<double>>& arg_data) {
            if (arg_data.size() != RowN) {
                log_and_throw<std::invalid_argument>(
                    "assign_with_vector", 
                    "arg_data must have the same size as RowN");
                throw;
            }
            for (auto it = arg_data.cbegin(); it != arg_data.cend(); ++it) {
                if ((*it).size() != ColN) {
                    log_and_throw<std::invalid_argument>(
                        "assign_with_vector", 
                        "all rows of arg_data must have the same size as ColN");
                    throw;
                }
            }
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    data[r][c] = arg_data[r][c];
                }
            }
            return *this;
        }

        inline bool operator==(const Matrix<RowN, ColN>& other) const {
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    if (data[r][c] != other[r][c]) {
                        return false;
                    }
                }
            }
            return true;
        }
        inline bool operator!=(const Matrix<RowN, ColN>& other) const {
            return !operator==(other);
        }

        inline std::array<double, ColN>& operator[](size_t index) {
            if (index >= RowN) {
                log_and_throw<std::out_of_range>(
                    "operator[](size_t index)", 
                    "index(" + std::to_string(index) + ") out of range (0 to RowN-1)"
                );
                throw;
            }
            return data[index];
        }
        inline const std::array<double, ColN>& operator[](size_t index) const {
            if (index >= RowN) {
                log_and_throw<std::out_of_range>(
                    "operator[](size_t index) const", 
                    "index(" + std::to_string(index) + ") out of range (0 to RowN-1)"
                );
                throw;
            }
            return data[index];
        }

        inline bool is_size_equal(size_t row_num, size_t col_num) const {
            return row_num == RowN && col_num == ColN;
        }

        inline std::array<double, RowN> get_column(size_t col_index) const {
            if (col_index >= ColN) {
                log_and_throw<std::out_of_range>(
                    "get_column(size_t col_index) const", 
                    "col_index out of range (0 to ColN-1)"
                );
                throw;
            }
            std::array<double, RowN> column;
            for (size_t i = 0; i < RowN; ++i) {
                column[i] = data[i][col_index];
            }
            return column;
        }

        inline Matrix<RowN, ColN> operator-() const { // negative operator
            Matrix<RowN, ColN> result;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    result[r][c] = -data[r][c];
                }
            }
            return result;
        }
        inline Matrix<RowN, ColN> operator+(const Matrix<RowN, ColN>& other) const {
            Matrix<RowN, ColN> result;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    result[r][c] = data[r][c] + other[r][c];
                }
            }
            return result;
        }
        inline Matrix<RowN, ColN> operator-(const Matrix<RowN, ColN>& other) const { // minus operator
            Matrix<RowN, ColN> result;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    result[r][c] = data[r][c] - other[r][c];
                }
            }
            return result;
        }
        template <size_t oColN>
        inline Matrix<RowN, oColN> operator*(const Matrix<ColN, oColN>& other) const {
            Matrix<RowN, oColN> result;
            double tmp;
            for (size_t rr = 0; rr < RowN; ++rr) {
                for (size_t rc = 0; rc < oColN; ++rc) {
                    tmp = 0;
                    for (size_t i = 0; i < ColN; ++i) {
                        tmp += data[rr][i] * other[i][rc];
                    }
                    result[rr][rc] = tmp;
                }
            }
            return result;
        }

        inline Matrix<RowN, ColN> operator*(double scalar) const {
            Matrix<RowN, ColN> result;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    result[r][c] = data[r][c] * scalar;
                }
            }
            return result;
        }
        inline Matrix<RowN, ColN> operator/(double scalar) const {
            if (scalar == 0) {
                log_and_throw(
                    "operator/(double scalar) const", 
                    "scalar cannot be 0");
                throw;
            }
            Matrix<RowN, ColN> result;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    result[r][c] = data[r][c] / scalar;
                }
            }
            return result;
        }
        
        inline Matrix<RowN, ColN>& operator+=(const Matrix<RowN, ColN>& other) noexcept {
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    data[r][c] += other[r][c];
                }
            }
            return *this;
        }
        inline Matrix<RowN, ColN>& operator-=(const Matrix<RowN, ColN>& other) noexcept {
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    data[r][c] -= other[r][c];
                }
            }
            return *this;
        }

        inline Matrix<RowN, ColN>& operator*=(double scalar) noexcept {
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    data[r][c] *= scalar;
                }
            }
            return *this;
        }
        inline Matrix<RowN, ColN>& operator/=(double scalar) {
            if (scalar == 0) {
                log_and_throw(
                    "operator/=(double scalar)", 
                    "scalar cannot be 0");
                throw;
            }
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    data[r][c] /= scalar;
                }
            }
            return *this;
        }
        
        inline Matrix<ColN, RowN> transpose() const {
            if (RowN == 1 && ColN == 1) {
                return Matrix<1, 1>(data[0][0]);
            }
            Matrix<ColN, RowN> result;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) { 
                    result[c][r] = data[r][c];
                }
            }
            return result;
        }


        inline std::string to_string(
            bool add_prefix = true, 
            std::string elem_sep = ", ", 
            std::string line_sep = "], \n [", 
            std::string front = "[[", 
            std::string end = "]]"
        ) const {
            std::string result;
            result += (add_prefix? "Matrix(\n" : "(\n") + front;
            for (size_t r = 0; r < RowN; ++r) {
                for (size_t c = 0; c < ColN; ++c) {
                    result += 
                        std::to_string(std::round(data[r][c])) 
                        + (c < ColN - 1? elem_sep : "");
                }
                result += (r < RowN - 1? line_sep : end);
            }
            result += "\n)";
            return result;
        }

        inline Matrix<RowN, ColN> T() const { return transpose(); }
        inline static constexpr Matrix<RowN, ColN> O() { return Matrix<RowN, ColN>(0); }

    private:
        
        void log(const std::string& func_name, const std::string& message, const Logger::LogLevel& log_level, bool add_timestamp) {
            Logger::log(
                "Matrix<" + std::to_string(RowN) + ", " 
                    + std::to_string(ColN) + ">::" 
                    + func_name, 
                message, 
                log_level, 
                add_timestamp
            );
        }

        template <typename ExceptionType = std::runtime_error>
        [[noreturn]] void log_and_throw(const std::string& func_name, const std::string& message) {
            Logger::log_and_throw<ExceptionType>(
                "Matrix<" + std::to_string(RowN) + ", " 
                    + std::to_string(ColN) + ">::" 
                    + func_name, 
                message);
        }

};

#endif // MATRIX_HPP