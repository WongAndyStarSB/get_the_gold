#include "Thruster.hpp"


std::string Thruster::to_string() const {
    return "Thrust( position: " + position.to_string() +
           ", direction: " + direction.to_string() +
           ", power: " + std::to_string(power) + " )";
}