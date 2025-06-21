#include "Vector2d.hpp"

#include <string>
#include <stdexcept>

std::string Vector2d::to_string() const {
    return "Vector2d( " + std::to_string(x) + "i + " + std::to_string(y) + "j )";
}



// operators
Vector2d Vector2d::operator+(const Vector2d& other) const {
    return Vector2d(x+other.x, y+other.y);
}
Vector2d Vector2d::operator-(const Vector2d& other) const {
    return Vector2d(x-other.x, y-other.y);
}
Vector2d Vector2d::operator*(double scalar) const {
    return Vector2d(x * scalar, y * scalar);
}
Vector2d Vector2d::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("Vector2d::operator/(double) ZeroDivisionError: divisor cannot be 0");
    }
    return Vector2d(x / scalar, y / scalar);
}
double Vector2d::dot_mul(const Vector2d& other) const {
    return x*other.x + y*other.y;
}
double Vector2d::scalar_cross_mul(const Vector2d& other) const {
    return x * other.y - y * other.x;
}
double Vector2d::abs() const {
    return sqrt(x*x + y*y);
}

bool Vector2d::is_equal(const Vector2d& other, double precision) const {
    return std::abs(x - other.x) < precision &&
           std::abs(y - other.y) < precision;
}