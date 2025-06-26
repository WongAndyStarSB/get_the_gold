#ifndef SHAPE_3D_HPP
#define SHAPE_3D_HPP

#include "Shape2d.hpp"

class Shape3d {
    protected:
        // The centre position of the shape in 3D space
        // This position is used to define the 3D shape in 3D space.
        // (absolute position in 3D space)
        Pos3d centre; 
        // The basis vectors of the shape in 3D space
        Matrix basis;
    public:
        inline explicit Shape3d(const Pos3d& arg_centre, const Matrix& arg_basis)
            : centre(arg_centre), basis(arg_basis)
        {}
        inline Shape3d(const Shape3d&) = default;
        inline Shape3d(Shape3d&&) = default;

        inline Shape3d& operator=(const Shape3d& other) = default;
        inline Shape3d& operator=(Shape3d&& other) = default;

        const Pos3d& get_center() const { return centre; }
        const Vector3d& get_normal() const { return normal; }

        void set_centre(const Pos3d& new_centre) { centre = new_centre; }
        void set_normal(const Vector3d& new_normal) { normal = new_normal.unit_vector(); }
};


class Sphere : public Shape3d {
    public:
        double radius;
        inline explicit Sphere(const Pos3d& centre_pos, const Vector3d& normal_vect, const double& r)
        : Shape3d(centre_pos, normal_vect), radius(r) {}
        Pos3d centre_pos() const { return centre; }
};

class Prism : public Shape3d {
    public:
        Shape2d base; // The base of the prism in 2D space
        double height; // Height of the prism in 3D space

        inline explicit Prism(
            const Pos3d& arg_centre, 
            const Shape2d& arg_base)
            : Shape3d(arg_centre, arg_base.surface.get_unit_normal_vector()), base(arg_base), height(arg_base.centre_pos.distance_to(arg_centre))
        {}
};










#endif // SHAPE_3D_HPP