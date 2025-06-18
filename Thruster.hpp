#ifndef THRUSTER_HPP
#define THRUSTER_HPP

#include <string>
#include "Pos3d.hpp"
#include "Vector3d.hpp"

class Thruster {
    public:
        Pos3d position; // Reletive position of the thruster in spaceship (reletive)
        Vector3d direction; // Direction of the thrust
        bool is_active; // Is the thruster active?
        unsigned int power; // Power of the thruster

        inline explicit Thruster(Pos3d pos, Vector3d dir, int pow = 1) 
            : position(pos), direction(dir), is_active(false), power(pow) {}

        inline Thruster(const Thruster&) = default;
        inline Thruster(Thruster&&) = default;

        std::string to_string() const;
};

#endif // THRUSTER_HPP