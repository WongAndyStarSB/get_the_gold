#include "_Matrix.hpp"

#include <stdexcept>

Matrix::Matrix(const std::vector<std::vector<double>>& arg_data, bool arg_is_size_changeable) 
    : data(arg_data), num_of_row(arg_data.size()), is_size_changeable(arg_is_size_changeable) {
        if (num_of_row == 0) {
            num_of_col = 0;
            return;
        }
        num_of_col = arg_data[0].size();
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (num_of_col != (*it).size()) {
                throw std::invalid_argument("Matrix::Matrix: UnequalRowSize: all rows must have the same number of columns");
            }
        }
}
Matrix::Matrix(size_t arg_num_of_row, size_t arg_num_of_col, double default_val, bool arg_is_size_changeable) 
    : num_of_row(arg_num_of_row), num_of_col(arg_num_of_col), is_size_changeable(arg_is_size_changeable) {
        data.resize(num_of_row);
        for (auto& row : data) {
            row.reserve(num_of_col);
            for (size_t i = 0; i < num_of_col; ++i) {
                row.emplace_back(default_val);
            }
        }

}
Matrix::Matrix(const Matrix& other, bool arg_is_size_changeable) 
    : num_of_row(other.num_of_row), num_of_col(other.num_of_col), data(other.data), is_size_changeable(arg_is_size_changeable) {
}
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    data = other.data;
    num_of_row = other.num_of_row;
    num_of_col = other.num_of_col;
    return *this;
}
Matrix& Matrix::operator=(const std::vector<std::vector<double>>& arg_data) {
    if (arg_data.empty()) {
        clear();
        return *this;
    }
    data = arg_data;
    num_of_row = data.size();
    // if (num_of_row == 0) {
    //     num_of_col = 0;
    //     return *this;
    // }
    num_of_col = data[0].size();
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (num_of_col != (*it).size()) {
            throw std::invalid_argument("Matrix::Matrix: UnequalRowSize: all rows must have the same number of columns");
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (num_of_row != other.num_of_row || num_of_col != other.num_of_col) {
        return false; // different dimensions
    }
    for (size_t r = 0; r < num_of_col; ++r) {
        for (size_t c = 0; c < num_of_row; ++c) {
            if (data[r][c] != other.data[r][c]) {
                return false; // different elements
            }
        }
    }
    return true; // all elements are equal
}

std::vector<double>& Matrix::operator[](size_t index) {
    if (index >= num_of_row) {
        throw std::out_of_range("Matrix::operator[]: IndexErr: Index out of range");
    }
    return data[index];
}
const std::vector<double>& Matrix::operator[](size_t index) const {
    if (index >= num_of_row) {
        throw std::out_of_range("Matrix::operator[]: IndexErr: Index out of range");
    }
    return data[index];
}


size_t Matrix::get_num_of_row() const {
    return num_of_row;
}
size_t Matrix::get_num_of_col() const {
    return num_of_col;
}
std::vector<std::vector<double>> Matrix::get_data() const {
    return data;
}
bool Matrix::is_size_equal(size_t row, size_t col) const {
    return (row == num_of_row) && (col = num_of_col);
}
std::vector<double> Matrix::get_column(size_t col_index) const {
    std::vector<double> vect;
    if (num_of_row == 0) {
        return vect;
    }
    if (col_index >= num_of_col) {
        throw std::out_of_range("Matrix::get_column: InvalidArgErr/IndexErr: col_index cannot be >= to num_of_col");
    }
    vect.reserve(num_of_row);
    for (const std::vector<double>& row : data) {
        vect.emplace_back(row[col_index]);
    }
    return vect;
}

void Matrix::resize(size_t new_num_of_row, size_t new_num_of_col, double default_val) {
    if (!is_size_changeable) {
        throw std::runtime_error("Matrix::resize ChangingNonChangeableSize");
    }
    if (new_num_of_row == 0) {
        data.clear();
        num_of_row = 0;
        num_of_col = 0;
        return;
    }
    data.resize(new_num_of_row);
    for (auto& row : data) {
        row.resize(new_num_of_col, default_val);
    }
    num_of_row = new_num_of_row;
    num_of_col = new_num_of_col;
}

void Matrix::resize(size_t new_num_of_row, double default_val) {
    if (!is_size_changeable) {
        throw std::runtime_error("Matrix::resize ChangingNonChangeableSize");
    }
    if (new_num_of_row == 0) {
        data.clear();
        num_of_row = 0;
        num_of_col = 0;
        return;
    }
    data.resize(new_num_of_row, std::vector<double>(num_of_col, default_val));
    num_of_row = new_num_of_row;
}

void Matrix::clear() {
    if (!is_size_changeable) {
        throw std::runtime_error("Matrix::resize ChangingNonChangeableSize");
    }
    data.clear();
    num_of_row = 0;
    num_of_col = 0;
}

void Matrix::emplace_back(const std::vector<double>& row) {
    if (!is_size_changeable) {
        throw std::runtime_error("Matrix::resize ChangingNonChangeableSize");
    }
    if (row.size() != num_of_col) {
        throw std::invalid_argument("Matrix::emplace_back: InvalidArgErr: Row size does not match matrix column size");
    }
    data.emplace_back(row);
    ++num_of_row;
}