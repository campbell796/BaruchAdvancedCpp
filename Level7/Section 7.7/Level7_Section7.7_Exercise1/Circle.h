#pragma once
#include "Shape.h"
#include "Point.h"
class Circle :
    public Shape
{
    Point* c_;
    double* r_;
public:
    Circle();  // Default constructor
    Circle(const Point& c, double r);  // Constructor point and radius
    Circle(const Circle& pt);  // Copy constructor
    Circle& operator=(const Circle& pt);  // Assignment operator
    Point CenterPoint();  // Return center point
    double Radius();  // Return radius
    void CenterPoint(Point centre);  // Set center point
    void Radius(double radius);  // Set radius

    //Print Function
    std::ostream& out(std::ostream& o) const
    {
        o << "Center: " << c_->x() << ", " << c_->y() << "; Radius: " << *r_ << std::endl;
        return o;
    }
};

