#ifndef SHAPE_2D_HPP
#define SHAPE_2D_HPP


#include "Pos3d.hpp"
#include "Vector3d.hpp"
#include "Surface.hpp"

class Shape2d {
    public:
        // The centre position of the shape in 3D space
        // This position is used to define the 2D shape in 3D space.
        // (absolute position in 3D space)
        Pos3d centre_pos; 
        // The surface on which the shape is defined
        // This surface is a 2D linear surface in 3D space.
        Surface surface;

        

        inline explicit Shape2d(
            const Pos3d& arg_centre_pos, 
            const Surface& arg_surface)
            : centre_pos(arg_centre_pos), 
              surface(arg_surface)
        {}

        Shape2d& operator=(const Shape2d& other);
};

class Circle : public Shape2d {
    public:
        double radius;
        inline explicit Circle(
            const Pos3d& arg_centre_pos, 
            const Surface& arg_surface, 
            const double& arg_radius)
            : Shape2d(arg_centre_pos, arg_surface), radius(arg_radius)
        {}

        Circle& operator=(const Circle& other);
};

class Rect : public Shape2d {
    public:
        double width;
        double height;

        inline explicit Rect(
            const Pos3d& arg_centre_pos, 
            const Surface& arg_surface, 
            double arg_width, 
            double arg_height)
            : Shape2d(arg_centre_pos, arg_surface), width(arg_width), height(arg_height)
        {}

        Rect& operator=(const Rect& other);

        // Getters for the positions of the corners
        Pos3d top_left_pos() const;
        Pos3d top_right_pos() const;
        Pos3d bottom_left_pos() const;
        Pos3d bottom_right_pos() const;

};



#endif // SHAPE_2D_HPP