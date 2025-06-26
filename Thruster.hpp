#ifndef THRUSTER_HPP
#define THRUSTER_HPP

#include <string>
#include "Pos3d.hpp"
#include "Vector3d.hpp"

class Thruster {
    public:
        Vector3d position; // Reletive position of the thruster in spaceship (reletive)
        Vector3d direction; // Direction of the thrust
        bool is_active; // Is the thruster active?
        unsigned int power; // Power of the thruster

        inline explicit Thruster(Vector3d pos, Vector3d dir, int pow = 1) 
            : position(pos), direction(dir), is_active(false), power(pow) {}

        inline Thruster(const Thruster&) = default;
        inline Thruster(Thruster&&) = default;

        std::string to_string() const;
        void activate() { is_active = true; }
        void deactivate() { is_active = false; }
        void set_power(unsigned int new_power) { power = new_power; }
        unsigned int get_power() const { return power; }
        Vector3d get_force() const;
        Vector3d get_torque() const;
};

#endif // THRUSTER_HPP