#include "Basis3d.hpp"

#include "stdexcept"


Basis3d::Basis3d(const std::vector<std::vector<double>>& arg_data)
    : Matrix(arg_data, false) {
    throw_if_not_3x3<std::invalid_argument>(); 
}
Basis3d::Basis3d(size_t arg_num_of_row, size_t arg_num_of_col, double default_val)
    : Matrix(arg_num_of_row, arg_num_of_col, default_val, false) {
    throw_if_not_3x3<std::invalid_argument>();
}

Vector3d Basis3d::local_to_world(const Vector2d& vect) const {
    return x_axis()*vect.x + y_axis()*vect.y;
}
Vector3d Basis3d::local_to_world(const Vector3d& vect) const {
    return x_axis()*vect.x + y_axis()*vect.y + z_axis()*vect.z;
}