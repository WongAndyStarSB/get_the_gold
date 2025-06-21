#include "Vector3d.hpp"

#include <string>
#include <stdexcept>

std::string Vector3d::to_string() const {
    return "Vector3d( " + std::to_string(x) + "i + " + std::to_string(y) + "j + " + std::to_string(z) + "k )";
}



// operators
Vector3d Vector3d::operator+(const Vector3d& other) const {
    return Vector3d(x+other.x, y+other.y, z+other.z);
}
Vector3d Vector3d::operator-(const Vector3d& other) const {
    return Vector3d(x-other.x, y-other.y, z-other.z);
}
Vector3d Vector3d::operator*(double scalar) const {
    return Vector3d(x * scalar, y * scalar, z * scalar);
}
Vector3d Vector3d::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("Vector3d::operator/(double) ZeroDivisionError: divisor cannot be 0");
    }
    return Vector3d(x / scalar, y / scalar, z / scalar);
}
double Vector3d::dot_mul(const Vector3d& other) const {
    return x*other.x + y*other.y + z*other.z;
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

bool Vector3d::is_equal(const Vector3d& other, double precision) const {
    return std::abs(x - other.x) < precision &&
           std::abs(y - other.y) < precision &&
           std::abs(z - other.z) < precision;
}
bool Vector3d::is_parallel(const Vector3d& other, double precision) const {
    // Check if the cross product is close to zero vector
    Vector3d cross = this->cross_mul(other);
    return cross.abs() < precision;
}