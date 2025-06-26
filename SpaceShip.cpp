#include "SpaceShip.hpp"


size_t SpaceShip::num_of_thrusters() const {
    return thrusters.size();
}

Vector3d SpaceShip::net_force() const {
    Vector3d net_force(0, 0, 0);
    for (const auto& thruster : thrusters) {
        net_force = net_force + thruster.get_force(); // Sum up the forces from all thrusters
    }
    return net_force;
}
Vector3d SpaceShip::net_torque() const {
    Vector3d net_torque(0, 0, 0);
    for (const auto& thruster : thrusters) {
        net_torque = net_torque + thruster.get_torque(); // Sum up the torques from all thrusters
    }
    return net_torque;
}

void SpaceShip::update_position(double delta_time_ms) {
    position = position + velocity * delta_time_ms / 1000; // Update position based on velocity and time
}