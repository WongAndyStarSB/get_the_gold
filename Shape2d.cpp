#include "Shape2d.hpp"

#include "Pos3d.hpp"
#include "Vector2d.hpp"
#include "Surface.hpp"
#include "Vector3d.hpp"

#include <cmath>
#include <stdexcept>


// Assignment operator of Shape2d
Shape2d& Shape2d::operator=(const Shape2d& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    top_left_pos = other.top_left_pos;
    surface = other.surface;
    return *this;
}

// Assignment operators of subclasses

Circle& Circle::operator=(const Circle& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    top_left_pos = other.top_left_pos;
    surface = other.surface;
    radius = other.radius;
    return *this;
}


Rect& Rect::operator=(const Rect& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    top_left_pos = other.top_left_pos;
    surface = other.surface;
    width = other.width;
    height = other.height;
    return *this;
}

// Getters for the positions of subclasses

Pos3d Circle::centre_pos() const {
    Vector3d v = surface.surface_to_world_vector(
        Vector2d(radius / surface.get_x_magnitude(), radius / surface.get_y_magnitude()));
    return top_left_pos + v;   
}





Pos3d Rect::top_right_pos() const {
    Vector3d v = surface.surface_to_world_vector(
        Vector2d(width / surface.get_x_magnitude(), 0)
    );
    return top_left_pos + v;
}
Pos3d Rect::bottom_left_pos() const {
    Vector3d v = surface.surface_to_world_vector(
        Vector2d(0, height / surface.get_y_magnitude()
    ));
    return top_left_pos + v;
}
Pos3d Rect::bottom_right_pos() const {
    Vector3d v = surface.surface_to_world_vector(
        Vector2d(
            width / surface.get_x_magnitude(), 
            height / surface.get_y_magnitude()
    ));
    return top_left_pos + v;
}