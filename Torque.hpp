#ifndef TORQUE_HPP
#define TORQUE_HPP

#include <string>
#include "Vector3d.hpp"
#include "Pos3d.hpp"


class Torque {
    private:
        Vector3d vector; // the cross product of r and F
    public:
        // Constructor
        explicit Torque(const Vector3d& arg_vector);
        explicit Torque(const Vector3d& r, const Vector3d& F);
        explicit Torque();
        
        inline Torque(const Torque&) = default;
        inline Torque(Torque&&) = default;

        const Vector3d& get_vector() const;
        double get_magnitude() const;
        Vector3d get_unit_vector() const;

        Torque operator+(Torque other) const;
        Torque operator-(Torque other) const;
        
};


#endif // TORQUE_HPP