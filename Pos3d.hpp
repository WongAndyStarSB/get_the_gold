#ifndef POS_3d_HPP
#define POS_3d_HPP

#include <string>
#include "Vector3d.hpp"

class Pos3d : public Vector3d{
    public:
        inline explicit Pos3d(const double& arg_x, const double& arg_y, const double& arg_z)
            : Vector3d(arg_x, arg_y, arg_z)
        {}
        inline Pos3d(const Pos3d&) = default;
        inline Pos3d(Pos3d&&) = default;

        // Assignment operator
        inline Pos3d operator=(const Pos3d& other) {
            if (this == &other) {
                return *this; // self-assignment check
            }
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }
        
        std::string to_string() const;


        double distance_to(const Pos3d& other) const;


        // Operators

        Pos3d operator+(const Vector3d& vect) const;
        Pos3d operator-(const Vector3d& vect) const;
        Vector3d operator-(const Pos3d& other) const;

        // Deleted operators
        inline double dot_mul(const Vector3d& other) const = delete;
        inline Vector3d cross_mul(const Vector3d& other) const = delete;


        bool operator==(const Pos3d& other) const;
};




#endif