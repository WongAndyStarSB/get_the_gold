#include "Pos3d.hpp"

#include <string>


std::string Pos3d::to_string() const {
    return "Pos3d( x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z) + " )";
}


// operators
Pos3d Pos3d::operator+(const Vector3d& vect) const {
    return Pos3d(x+vect.x, y+vect.y, z+vect.z);
}
Pos3d Pos3d::operator-(const Vector3d& vect) const {
    return Pos3d(x-vect.x, y-vect.y, z-vect.z);
}
bool Pos3d::operator==(const Pos3d& other) const {
    return (x == other.x && y == other.y && z == other.z);
}
