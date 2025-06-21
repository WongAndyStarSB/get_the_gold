#include "Surface.hpp"

#include <stdexcept>

#include "Utils.hpp"
#include "Vector2d.hpp"
#include "Vector3d.hpp"
#include "Matrix.hpp"


void Surface::compute_cache() const {
    x_vector_cache = Vector3d(basis_matrix[0][0], basis_matrix[1][0], basis_matrix[2][0]);
    y_vector_cache = Vector3d(basis_matrix[0][1], basis_matrix[1][1], basis_matrix[2][1]);
    normal_vector_cache = x_vector_cache.cross_mul(y_vector_cache);
    x_magnitude_cache = x_vector_cache.abs();
    y_magnitude_cache = y_vector_cache.abs();
    unit_x_vector_cache = x_vector_cache / x_magnitude_cache;
    unit_y_vector_cache = y_vector_cache / y_magnitude_cache;
    cache_valid = true;
}



explicit Surface::Surface(const Matrix& arg_basis_matrix) : basis_matrix(arg_basis_matrix), cache_valid(false) {
    set_basis(arg_basis_matrix); // Validate and set the basis matrix
}




void Surface::set_basis(const Matrix& new_basis_matrix) {
    if (new_basis_matrix.get_num_of_col() != 2 || new_basis_matrix.get_num_of_row() != 3) {
        throw std::invalid_argument("Surface::set_basis: InvalidArgErr: xy must be a matrix with 2 columns and 3 rows");
    }
    if (Utils::double_equal(new_basis_matrix[0][0], 0) || Utils::double_equal(new_basis_matrix[1][0], 0)) {
        throw std::invalid_argument("Surface::set_basis: InvalidArgErr: x vector cannot be a zero vector");
    }
    if (Utils::double_equal(new_basis_matrix[0][1], 0) || Utils::double_equal(new_basis_matrix[1][1], 0)) {
        throw std::invalid_argument("Surface::set_basis: InvalidArgErr: y vector cannot be a zero vector");
    }
    basis_matrix = new_basis_matrix;
    cache_valid = false; // Invalidate the cache
    compute_cache(); // Recompute the cache with the new basis matrix
}



Vector3d Surface::get_x_vector() const {
    if (!cache_valid) {
        compute_cache();
    }
    return x_vector_cache;
}
Vector3d Surface::get_y_vector() const {
    if (!cache_valid) {
        compute_cache();
    }
    return y_vector_cache;
}
Vector3d Surface::get_normal_vector() const {
    if (!cache_valid) {
        compute_cache();
    }
    return normal_vector_cache;
}

double Surface::get_x_magnitude() const {
    if (!cache_valid) {
        compute_cache();
    }
    return x_magnitude_cache;
}
double Surface::get_y_magnitude() const {
    if (!cache_valid) {
        compute_cache();
    }
    return y_magnitude_cache;
}
Vector3d Surface::get_unit_x_vector() const {
    if (!cache_valid) {
        compute_cache();
    }
    return unit_x_vector_cache;
}
Vector3d Surface::get_unit_y_vector() const {
    if (!cache_valid) {
        compute_cache();
    }
    return unit_y_vector_cache;
}



Vector3d Surface::surface_to_world_vector(const Vector2d& vect_in_surface) const {
    return get_x_vector() * vect_in_surface.x + get_y_vector() * vect_in_surface.y;
}