#include "Vector3d.hpp"

#include <string>
#include <vector>
#include <stdexcept>


Vector3d::Vector3d(const std::vector<double>& std_vector) 
    : x(std_vector[0]), y(std_vector[1]), z(std_vector[2]) { 
        if (std_vector.size() > 3) { throw std::invalid_argument("Vector3d::Vector3d InvalidArg std_vector should have length = 3"); }
}


std::string Vector3d::to_string(bool add_prefix) const {
    return 
        (add_prefix? "Vector3d( " : "(") 
        + std::to_string(x) + "i + " 
        + std::to_string(y) + "j + " 
        + std::to_string(z) + "k )";
}



// operators
double& Vector3d::operator[](size_t index) {
    switch (index) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::invalid_argument("Vector3d::operator[] InvalidArg: index out of range (0-2)");
    }
}
const double& Vector3d::operator[](size_t index) const {
    switch (index) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::invalid_argument("Vector3d::operator[] InvalidArg: index out of range (0-2)");
    }
}


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
double Vector3d::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}
Vector3d Vector3d::unit_vector() const {
    if (is_equal(Vector3d(0, 0, 0))) {
        return Vector3d(0, 0, 0); // Return zero vector if magnitude is zero
    }
    double mag = magnitude();
    return Vector3d(x / mag, y / mag, z / mag);
}

bool Vector3d::is_zero_vector(double precision) const {
    return is_equal(Vector3d::zero_vector(), precision);
}
bool Vector3d::is_equal(const Vector3d& other, double precision) const {
    return std::abs(x - other.x) < precision &&
           std::abs(y - other.y) < precision &&
           std::abs(z - other.z) < precision;
}
bool Vector3d::is_parallel(const Vector3d& other, double precision) const {
    // Check if the cross product is close to zero vector
    return cross_mul(other).magnitude() < precision;
}
bool Vector3d::is_perpendicular(const Vector3d& other, double precision) const {
    // Check if the dot product is close to zero
    return abs(dot_mul(other)) < precision;
}


Vector3d Vector3d::zero_vector() {
    return Vector3d(0, 0, 0);
}