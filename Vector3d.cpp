#include "Vector3d.hpp"

#include <string>

std::string Vector3d::to_string() const {
    return "Vector3d( " + std::to_string(x) + "i + " + std::to_string(y) + "j + " + std::to_string(z) + "k )";
}



// operators
bool Vector3d::operator==(const Vector3d& other) const {
    return (x == other.x && y == other.y && z == other.z);
}
Vector3d Vector3d::operator+(const Vector3d& other) const {
    return Vector3d(x+other.x, y+other.y, z+other.z);
}
Vector3d Vector3d::operator-(const Vector3d& other) const {
    return Vector3d(x-other.x, y-other.y, z-other.z);
}
Vector3d Vector3d::operator*(int scalar) const {
    return Vector3d(x * scalar, y * scalar, z * scalar);
}
Vector3d Vector3d::operator/(int scalar) const {
    return Vector3d(x / scalar, y / scalar, z / scalar);
}
int Vector3d::dot_mul(const Vector3d& other) const {
    return int(x*other.x + y*other.y + z*other.z);
}
Vector3d Vector3d::cross_mul(const Vector3d& other) const {
    return Vector3d(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}
double Vector3d::abs() const {
    return sqrt(x*x + y*y + z*z);
}