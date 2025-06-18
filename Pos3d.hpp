#ifndef POS_3d_HPP
#define POS_3d_HPP

#include <string>
#include "Vector3d.hpp"

class Pos3d {
    public:
        int x;
        int y;
        int z;
        inline explicit Pos3d(int arg_x, int arg_y, int arg_z) 
            : x(arg_x), y(arg_y), z(arg_z)
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

        Pos3d operator+(const Vector3d& vect) const;
        Pos3d operator-(const Vector3d& vect) const;

        bool operator==(const Pos3d& other) const;
};




#endif