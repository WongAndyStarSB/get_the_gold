#ifndef SPACE_SHIP_HPP
#define SPACE_SHIP_HPP

#include <array>
#include <vector>
#include "Pos3d.hpp"
#include "Vector3d.hpp"
#include "Thruster.hpp"

class SpaceShip {
    public:
        Pos3d position; // Position of the spaceship in space
        Vector3d velocity; // Velocity of the spaceship in space 
        std::vector<Thruster> thrusters; // Array of thrusters
        Vector3d facing_direction; // Facing direction of the spaceship

        inline explicit SpaceShip(Pos3d pos, Vector3d vel, std::vector<Thruster> thrusters_vect)
            : position(pos), velocity(vel), thrusters(std::move(thrusters_vect)), facing_direction(1, 0, 0) 
        {}
        inline SpaceShip(const SpaceShip&) = default;
        inline SpaceShip(SpaceShip&&) = default;

        size_t num_of_thrusters() const;
        Vector3d net_force() const;
        
        void update_position(size_t delta_time_ms);

        
        
};





#endif