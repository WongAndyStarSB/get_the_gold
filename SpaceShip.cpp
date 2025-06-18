#include "SpaceShip.hpp"


size_t SpaceShip::num_of_thrusters() const {
    return thrusters.size();
}

Vector3d SpaceShip::net_force() const {
    Vector3d net_force(0, 0, 0);
    for (const auto& thruster : thrusters) {
        if (thruster.is_active) {
            net_force = net_force + thruster.direction * thruster.power;
        }
    }
    return net_force;
}

void SpaceShip::update_position(size_t delta_time_ms) {
    position = position + velocity * delta_time_ms / 1000; // Update position based on velocity and time
}