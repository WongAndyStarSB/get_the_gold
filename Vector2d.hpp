#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

#include <string>

class Vector2d {
    public:
        double x;
        double y;

        inline explicit Vector2d(double arg_x, double arg_y)
            : x(arg_x), y(arg_y)
        {}

        inline Vector2d(const Vector2d&) = default;
        inline Vector2d(Vector2d&&) = default;

        // Assignment operator
        inline Vector2d operator=(const Vector2d& other) {
            if (this == &other) {
                return *this; // self-assignment check
            }
            x = other.x;
            y = other.y;
            return *this;
        }

        std::string to_string() const;

        // Operators
        
        Vector2d operator+(const Vector2d& other) const;
        Vector2d operator-(const Vector2d& other) const;
        Vector2d operator*(double scalar) const;
        Vector2d operator/(double scalar) const;
        double dot_mul(const Vector2d& other) const;
        double scalar_cross_mul(const Vector2d& other) const;
        double abs() const;

        bool is_equal(const Vector2d& other, double precision) const;
};

#endif // VECTOR_2D_HPP