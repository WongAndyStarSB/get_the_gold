#ifndef VECTOR_3d_HPP
#define VECTOR_3d_HPP

#include <string>

class Vector3d {
    public:
        int x;
        int y;
        int z;
        inline explicit Vector3d(int arg_x, int arg_y, int arg_z) 
            : x(arg_x), y(arg_y), z(arg_z) 
        {}
        inline Vector3d(const Vector3d&) = default;
        inline Vector3d(Vector3d&&) = default;

        

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

        std::string to_string() const;

        // Operators
        bool operator==(const Vector3d& other) const;
        Vector3d operator+(const Vector3d& other) const;
        Vector3d operator-(const Vector3d& other) const;
        Vector3d operator*(int scalar) const {
            return Vector3d(x * scalar, y * scalar, z * scalar);
        }
        Vector3d operator/(int scalar) const {
            return Vector3d(x / scalar, y / scalar, z / scalar);
        }
        int dot_mul(const Vector3d& other) const;
        Vector3d cross_mul(const Vector3d& other) const;
        double abs() const;
};




#endif