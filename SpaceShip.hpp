#ifndef SPACE_SHIP_HPP
#define SPACE_SHIP_HPP

#include <array>
#include <vector>
#include "Pos3d.hpp"
#include "Vector3d.hpp"
#include "Shape3d.hpp"
#include "Thruster.hpp"

class SpaceShip {
    public:
        Pos3d position; // Position of the spaceship in space
        Vector3d velocity; // Velocity of the spaceship in space 
        Vector3d angular_velocity; // Angular velocity of the spaceship in space
        std::vector<Thruster> thrusters; // Resizeable list of thrusters
        // Shape3d shape; // Shape of the spaceship in 3D space

        inline explicit SpaceShip(Pos3d pos, Vector3d vel, std::vector<Thruster> thrusters_vect)
            : position(pos), velocity(vel), thrusters(std::move(thrusters_vect))
        {}
        inline SpaceShip(const SpaceShip&) = default;
        inline SpaceShip(SpaceShip&&) = default;

        size_t num_of_thrusters() const;
        Vector3d net_force() const;
        Vector3d net_torque() const;
        
        void update(double delta_time_ms);

        void update_velocity(double delta_time_ms);
        void update_angular_velocity(double delta_time_ms);

        void update_position(double delta_time_ms);
        void update_facing_direction(double delta_time_ms);
        
        
};





#endif