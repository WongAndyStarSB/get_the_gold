#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix {
    private:
        std::vector<std::vector<double>> data;
        size_t num_of_row;
        size_t num_of_col;
    public:
        explicit Matrix(const std::vector<std::vector<double>>& arg_data);
        explicit Matrix(size_t arg_num_of_row, size_t arg_num_of_col, double default_val = 0.0);
        inline Matrix(const Matrix&) = default;
        inline Matrix(Matrix&&) = default;

        Matrix& operator=(const Matrix& other);
        inline Matrix& operator=(Matrix&& other) noexcept = default;
        Matrix& operator=(const std::vector<std::vector<double>>& other);

        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        std::vector<double>& operator[](size_t index);
        const std::vector<double>& operator[](size_t index) const;

        size_t get_num_of_row() const;
        size_t get_num_of_col() const;
        std::vector<std::vector<double>> get_data() const;

        void resize(size_t new_num_of_row, size_t new_num_of_col, double default_val);
        void resize(size_t new_num_of_row, double default_val = 0.0);

        void clear();
        void emplace_back(const std::vector<double>& row);
        
};

#endif // MATRIX_HPP