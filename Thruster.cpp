#include "Thruster.hpp"


std::string Thruster::to_string() const {
    return "Thrust( position: " + position.to_string() +
           ", direction: " + direction.to_string() +
           ", power: " + std::to_string(power) + " )";
}

Vector3d Thruster::get_force() const {
    return is_active ? direction * power : Vector3d(0, 0, 0);
}
Vector3d Thruster::get_torque() const {
    return is_active ? position.cross_mul(get_force()) : Vector3d(0, 0, 0);
}