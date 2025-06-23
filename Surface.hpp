#ifndef SURFACE_HPP
#define SURFACE_HPP


#include "Matrix.hpp"
#include "Vector2d.hpp"
#include "Vector3d.hpp"

class Surface {
    private:
        Matrix basis_matrix; // a 3x2 matrix representing the x and y coordinates of the 2d linear surface in 3d space
        mutable Vector3d x_vector_cache;
        mutable Vector3d y_vector_cache;
        mutable Vector3d normal_vector_cache;
        mutable Vector3d normal_unit_vector_cache;
        mutable double x_magnitude_cache;
        mutable double y_magnitude_cache;
        mutable Vector3d unit_x_vector_cache;
        mutable Vector3d unit_y_vector_cache;
        mutable bool cache_valid = false;   
        
        void compute_cache() const;
    public:
        explicit Surface(const Matrix& arg_basis_matrix);
        inline Surface(const Surface&) = default;
        inline Surface(Surface&&) = default;

        Surface& operator=(const Surface& other) = default;
        Surface& operator=(Surface&& other) = default;

        inline bool operator==(const Surface& other) const {
            return basis_matrix == other.basis_matrix;
        }
        inline bool operator!=(const Surface& other) const {
            return !(*this == other);
        }

        void set_basis(const Matrix& new_basis_matrix);
        // Getters
        inline const Matrix& get_basis() const { return basis_matrix; }
        Vector3d get_x_vector() const;
        Vector3d get_y_vector() const;
        Vector3d get_normal_vector() const;
        Vector3d get_unit_normal_vector() const;
        double get_x_magnitude() const;
        double get_y_magnitude() const;
        Vector3d get_unit_x_vector() const;
        Vector3d get_unit_y_vector() const;

        Vector3d surface_to_world_vector(const Vector2d& vect_in_surface) const;
};



#endif // SURFACE_HPP