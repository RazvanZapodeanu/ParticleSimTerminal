#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <cmath>

class Vector2D {
private:
    double x;
    double y;
public:
    Vector2D(double x=0.0, double y=0.0) : x(x), y(y) {}

    Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}

    Vector2D& operator=(const Vector2D& other) {
        if (this !=&other) {
            x=other.x;
            y=other.y;
        }
        return *this;
    }
    ~Vector2D() {}

    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x) { this->x=x; }
    void setY(double y) { this->y=y; }

    double magnitude() const {
        return std::sqrt(x*x + y*y);
    }
    void normalize(){
        double mag = magnitude();
        if (mag>0) {
            x/=mag;
            y/=mag;
        }
    }

    Vector2D normalized() const {
        Vector2D result(*this);
        result.normalize();
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << "," << v.y << ")";
        return os;
    }
};


#endif
