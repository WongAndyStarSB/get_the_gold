#ifndef VECTOR_3d_HPP
#define VECTOR_3d_HPP

#include <string>

class Vector3d {
    public:
        double x;
        double y;
        double z;
        inline explicit Vector3d()
            : x(0.0), y(0.0), z(0.0) 
        {}
        inline explicit Vector3d(double arg_x, double arg_y, double arg_z) 
            : x(arg_x), y(arg_y), z(arg_z) 
        {}
        inline Vector3d(const Vector3d&) = default;
        inline Vector3d(Vector3d&&) = default;
        Vector3d(const std::vector<double>& std_vector);

        

        // Assignment operator
        inline Vector3d operator=(const Vector3d& other) {
            if (this == &other) {
                return *this; // self-assignment check
            }
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        std::string to_string(bool add_prefix = true) const;

        // Operators

        double& operator[](size_t index);
        const double& operator[](size_t index) const;

        Vector3d operator+(const Vector3d& other) const;
        Vector3d operator-(const Vector3d& other) const;
        Vector3d operator*(double scalar) const;
        Vector3d operator/(double scalar) const;
        double dot_mul(const Vector3d& other) const;
        Vector3d cross_mul(const Vector3d& other) const;
        double magnitude() const;
        Vector3d unit_vector() const;

        bool is_zero_vector(double precision = 1e-6) const;
        bool is_equal(const Vector3d& other, double precision = 1e-6) const;
        bool is_parallel(const Vector3d& other, double precision = 1e-6) const;
        bool is_perpendicular(const Vector3d& other, double precision = 1e-6) const;

        static Vector3d zero_vector();
};




#endif