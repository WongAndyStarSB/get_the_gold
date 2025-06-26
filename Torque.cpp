#include "Torque.hpp"


explicit Torque::Torque(const Vector3d& arg_vector)
    : vector(arg_vector) {
    // Constructor initializes the torque vector
}
explicit Torque::Torque(const Vector3d& r, const Vector3d& F) 
    : vector(r.cross_mul(F)) {
    // Constructor initializes the torque vector as the cross product of r and F
}
explicit Torque::Torque() 
    : vector(Vector3d()) {
    // Default constructor initializes the torque vector to zero
}


const Vector3d& Torque::get_vector() const {
    return vector;
}
double Torque::get_magnitude() const {
    return vector.magnitude();
}
Vector3d Torque::get_unit_vector() const {
    return vector.unit_vector();
}

Torque Torque::operator+(Torque other) const {
    return Torque(vector + other.vector);
}
Torque Torque::operator-(Torque other) const {
    return Torque(vector - other.vector);
}