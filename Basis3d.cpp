#include "Basis3d.hpp"

#include <stdexcept>
#include <tuple>

#include "Logger.hpp"



Basis3d::Basis3d(const std::vector<std::vector<double>>& arg_data)
    : SquareMatrix<3>(arg_data) {
    throw_if_not_3x3<std::invalid_argument>("Basis3d");
    throw_if_basis_not_perpendicular<std::invalid_argument>("Basis3d");
}
Basis3d::Basis3d(const Vector3d& x, const Vector3d& y, const Vector3d& z)
    : SquareMatrix<3>(0) {
    bool x_is_zero = x.is_zero_vector();
    bool y_is_zero = y.is_zero_vector();
    bool z_is_zero = z.is_zero_vector();
    
    if ((x_is_zero && y_is_zero) 
        || (y_is_zero && z_is_zero) 
        || (z_is_zero && x_is_zero)
    ) {
        Logger::log_and_throw<std::invalid_argument>(
            "Basis3d::Basis3d", 
            "Basis3d cannot be created with only 1 axis vector provided");
    }
    
    if (z_is_zero) { set_basis_xy(x, y); return; }
    if (x_is_zero) { set_basis_yz(y, z); return; }
    if (y_is_zero) { set_basis_zx(z, x); return; }

    set_basis(x, y, z);
}
Basis3d::Basis3d(const SquareMatrix<3>& sq_matrix) 
    : SquareMatrix<3>(sq_matrix) {
}
Basis3d::Basis3d() 
    : SquareMatrix<3>(IdentityMatrix()) {
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

std::tuple<Vector3d, Vector3d, Vector3d> Basis3d::get_axes() const {
    SquareMatrix<3> tmp = this->T();
    return {Vector3d(tmp[0]), Vector3d(tmp[1]), Vector3d(tmp[2])};
}

Matrix<3, 2> Basis3d::get_xy_matrix() const {
    return this->get_sub_matrix<3, 2>(0, 0);
}


Vector3d Basis3d::local_to_world(const Vector2d& vect) const {
    return x_axis()*vect.x + y_axis()*vect.y;
}
Vector3d Basis3d::local_to_world(const Vector3d& vect) const {
    return x_axis()*vect.x + y_axis()*vect.y + z_axis()*vect.z;
}

void Basis3d::transform(const SquareMatrix<3>& transformer) {
    operator*=(transformer);
}
void Basis3d::normalized_transform(const SquareMatrix<3>& transformer) {
    SquareMatrix<3> t(transformer.T());
    for (size_t i = 0; i < 3; ++i) {
        t[i] = Vector3d(t[i]).unit_vector().to_array();
    }
    operator*=(t.T());
}



void Basis3d::set_basis_no_check(const Vector3d& x, const Vector3d& y, const Vector3d& z) {
    for (unsigned int i = 0; i < 3; ++i) {
        operator[](i)[0] = x[i];
        operator[](i)[1] = y[i];
        operator[](i)[2] = z[i];
    }
}
