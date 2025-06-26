#ifndef SHAPE_2D_HPP
#define SHAPE_2D_HPP


#include "Pos3d.hpp"
#include "Vector2d.hpp"
#include "Vector3d.hpp"
#include "Basis3d.hpp"

class Shape2d {
    public:
        // The centre position of the shape in 3D space
        // This position is used to define the 2D shape in 3D space.
        // (absolute position in 3D space)
        Pos3d centre;
        Basis3d basis;


        inline explicit Shape2d(
            const Pos3d& centre_pos, 
            const Basis3d& arg_basis)
            : centre(centre_pos), 
              basis(arg_basis) {
            if (!arg_basis.is_size_equal(3, 3)) {
                throw std::invalid_argument("Shape2d::Shape2d InvalidArgErr: arg_basis must be 3x3");
            }
        }

        Shape2d& operator=(const Shape2d& other);


        Vector3d to_world(const Vector2d& vect) const;

};

class Circle : public Shape2d {
    public:
        double radius;
        inline explicit Circle(
            const Pos3d& centre_pos, 
            const Basis3d& arg_basis, 
            const double& arg_radius)
            : Shape2d(centre_pos, arg_basis), radius(arg_radius)
        {}

        Circle& operator=(const Circle& other);
};

class Rect : public Shape2d {
    public:
        double width;
        double height;

        inline explicit Rect(
            const Pos3d& centre_pos, 
            const Basis3d& arg_basis, 
            double arg_width, 
            double arg_height)
            : Shape2d(centre_pos, arg_basis), width(arg_width), height(arg_height)
        {}

        Rect& operator=(const Rect& other);

        // Getters for the positions of the corners
        Pos3d top_left_pos() const;
        Pos3d top_right_pos() const;
        Pos3d bottom_left_pos() const;
        Pos3d bottom_right_pos() const;

};



#endif // SHAPE_2D_HPP