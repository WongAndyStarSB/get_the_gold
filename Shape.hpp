#ifndef SHAPE_HPP
#define SHAPE_HPP


#include "Pos3d.hpp"

class Shape {
    public:
        Pos3d top_left_pos;


        Shape(Pos3d arg_top_left_pos)
            : top_left_pos(
                arg_top_left_pos.x, 
                arg_top_left_pos.y, 
                arg_top_left_pos.z
              ) 
        {}
};

class Circle : public Shape {
    public:
        int radius;
        Circle(Pos3d arg_top_left_pos, int arg_radius)
            : Shape(top_left_pos), radius(arg_radius)
        {}
        Pos3d centre_pos() const;
};
class Rect : public Shape {
    public:
        int width;
        int height;

        Rect(Pos3d arg_top_left_pos, int arg_width, int arg_height)
            : Shape(arg_top_left_pos), width(arg_width), height(arg_height)
        {}
};



#endif // SHAPE_HPP