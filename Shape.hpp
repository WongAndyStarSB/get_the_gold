#ifndef SHAPE_HPP
#define SHAPE_HPP


#include "Pos3d.hpp"

class Shape {
    public:
        Pos3d top_left_pos;
        Vector3d normal_vect;


        Shape(
            const Pos3d& arg_top_left_pos, 
            const Vector3d& arg_normal_vect)
            : top_left_pos(
                arg_top_left_pos.x, 
                arg_top_left_pos.y, 
                arg_top_left_pos.z), 
              normal_vect()
        {}
};

class Circle : public Shape {
    public:
        int radius;
        Circle(
            const Pos3d& arg_top_left_pos, 
            const Vector3d& arg_normal_vect, int arg_radius)
            : Shape(top_left_pos, arg_normal_vect), radius(arg_radius)
        {}
        Pos3d centre_pos() const;
};
class Rect : public Shape {
    public:
        int width;
        int height;

        Rect(
            const Pos3d& arg_top_left_pos, 
            const Vector3d& arg_normal_vect, 
            int arg_width, 
            int arg_height)
            : Shape(arg_top_left_pos, arg_normal_vect), width(arg_width), height(arg_height)
        {}
        Pos3d top_right_pos();
        Pos3d bottom_left_pos();
        Pos3d bottom_right_pos();

};



#endif // SHAPE_HPP