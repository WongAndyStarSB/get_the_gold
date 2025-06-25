#include "Basis3d.hpp"

#include <stdexcept>



Basis3d::Basis3d(const std::vector<std::vector<double>>& arg_data)
    : Matrix(arg_data, false) {
    throw_if_not_3x3<std::invalid_argument>("Basis3d");
    throw_if_basis_not_perpendicular<std::invalid_argument>("Basis3d");
}
Basis3d::Basis3d(const Vector3d& x, const Vector3d& y, const Vector3d& z)
    : Matrix(3, 3, 0, false) {
    bool x_is_zero = x.is_zero_vector();
    bool y_is_zero = y.is_zero_vector();
    bool z_is_zero = z.is_zero_vector();
    
    if ((x_is_zero && y_is_zero) 
        || (y_is_zero && z_is_zero) 
        || (z_is_zero && x_is_zero)
    ) {
        throw std::invalid_argument("Basis3d::Basis3d InvalidArg: Basis3d cannot be created with only 1 axis vector provided");
    }
    
    if (z_is_zero) { set_basis_xy(x, y); return; }
    if (x_is_zero) { set_basis_yz(y, z); return; }
    if (y_is_zero) { set_basis_zx(z, x); return; }

    set_basis(x, y, z);
}
Basis3d::Basis3d() 
    : Matrix(3, 3, 0) {
    for (unsigned int i = 0; i < 3; ++i) {
        operator[](i)[i] = 1;
    }
}

void Basis3d::set_basis_xy(const Vector3d& x, const Vector3d& y) {
    throw_if_not_perpendicular<std::invalid_argument>(x, y, "set_basis");
    set_basis_no_check(
        x.unit_vector(), 
        y.unit_vector(), 
        x.cross_mul(y).unit_vector()
    );
}
void Basis3d::set_basis_yz(const Vector3d& y, const Vector3d& z) {
    throw_if_not_perpendicular<std::invalid_argument>(y, z, "set_basis");
    set_basis_no_check(
        y.cross_mul(z).unit_vector(), 
        y.unit_vector(), 
        z.unit_vector()
    );
}
void Basis3d::set_basis_zx(const Vector3d& z, const Vector3d& x) {
    throw_if_not_perpendicular<std::invalid_argument>(z, x, "set_basis");
    set_basis_no_check(
        x.unit_vector(), 
        z.cross_mul(x).unit_vector(), 
        z.unit_vector()
    );
}

void Basis3d::set_basis(const Vector3d& x, const Vector3d& y, const Vector3d& z) {
    throw_if_not_perpendicular<std::invalid_argument>(x, y, z, "set_basis");
    set_basis_no_check(
        x.unit_vector(),
        y.unit_vector(),
        z.unit_vector()
    );
}

Vector3d Basis3d::local_to_world(const Vector2d& vect) const {
    return x_axis()*vect.x + y_axis()*vect.y;
}
Vector3d Basis3d::local_to_world(const Vector3d& vect) const {
    return x_axis()*vect.x + y_axis()*vect.y + z_axis()*vect.z;
}

void Basis3d::set_basis_no_check(const Vector3d& x, const Vector3d& y, const Vector3d& z) {for (unsigned int i = 0; i < 3; ++i) {
        operator[](i)[0] = x[i];
        operator[](i)[1] = y[i];
        operator[](i)[2] = z[i];
    }
}