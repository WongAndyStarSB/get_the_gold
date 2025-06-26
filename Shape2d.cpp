#include "Shape2d.hpp"

#include "Pos3d.hpp"
#include "Vector2d.hpp"
#include "Matrix.hpp"
#include "Vector3d.hpp"

#include <cmath>
#include <stdexcept>


// Assignment operator of Shape2d
Shape2d& Shape2d::operator=(const Shape2d& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    centre = other.centre;
    basis = other.basis;
    return *this;
}
// Assignment operators of subclasses

Circle& Circle::operator=(const Circle& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    centre = other.centre;
    basis = other.basis;
    radius = other.radius;
    return *this;
}


Rect& Rect::operator=(const Rect& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    centre = other.centre;
    basis = other.basis;
    width = other.width;
    height = other.height;
    return *this;
}

// Getters for the positions of subclasses






Pos3d Rect::top_left_pos() const {
    return centre + basis.local_to_world(Vector2d(-width/2, height/2));
}


Pos3d Rect::top_right_pos() const {
    return centre + basis.local_to_world(Vector2d(width/2, height/2));
}

Pos3d Rect::bottom_left_pos() const {
    return centre + basis.local_to_world(Vector2d(-width/2, -height/2));
}

Pos3d Rect::bottom_right_pos() const {
    return centre + basis.local_to_world(Vector2d(width/2, -height/2));
}