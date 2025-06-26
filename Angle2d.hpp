#ifndef ANGLE_2D_HPP
#define ANGLE_2D_HPP

#include <cmath>
#include <numbers>
#include <stdexcept>


class Angle2d {
    public:
        double value;
        double to_degree() { return value * 180 / std::numbers::pi; } // name followed by '::' must be a class or namespace nameC/C++(276)
};

#endif // ANGLE_2D_HPP