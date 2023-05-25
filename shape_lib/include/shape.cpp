#include "shape.h"

std::ostream& operator<<(std::ostream& out, const Coordinate& coordinate)  
{
    out << coordinate.x << "\t" << coordinate.y << "\t" << coordinate.z << "\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) 
{
    out << vector.i << "\t" << vector.j << "\t" << vector.k << "\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const ShapeType& type)
{
    switch (type)
    {
    case ShapeType::CIRCLE:
        out << "Circle";
        break;
    
    case ShapeType::ELLIPSE: 
        out << "Ellipse";
        break;

    case ShapeType::HELIX: 
        out << "Helix";
        break;
    }
    return out;
}

Circle::Circle(double x0, double y0, double radius)
{
    center_.x = x0;
    center_.y = y0;
    radius_ = radius;
}

Coordinate Circle::GetCoordinate(double parameter)
{
    double x = center_.x + radius_ * cos(parameter);
    double y = center_.y + radius_ * sin(parameter);
    return Coordinate({x, y, 0});
}

//y'x = y't/x't -> y't = -(r * cos(t))' / (r * sin(t))'
Vector Circle::GetFirstDerivate(double parameter)
{   
    double dx = -radius_ * cos(parameter);
    double dy =  radius_ * sin(parameter);
    return Vector({dx, dy, 0});
}

ShapeType Circle::GetType() 
{
    return type_;
}

double Circle::GetRadius()
{
    return radius_;
}

Ellipse::Ellipse(double x0, double y0, double rad1, double rad2) 
{
    center_.x = x0;
    center_.y = y0;
    radiusx_a_ = rad1;
    radiusy_b_ = rad2;
}

Coordinate Ellipse::GetCoordinate(double parameter)
{
    double a = radiusx_a_ + center_.x;
    double b = radiusy_b_ + center_.y;

    double x = center_.x + a * cos(parameter);
    double y = center_.y + b * sin(parameter);

    return Coordinate({x, y, 0});
}

//y'x = y't/x't -> y't = (a * cos(t))' / (b * sin(t))' -> y't = -(a * sin(t)) / (b * cos(t))
Vector Ellipse::GetFirstDerivate(double parameter) 
{
    double dx = -radiusx_a_ * sin(parameter);
    double dy =  radiusy_b_ * cos(parameter);
    return Vector({dx, dy, 0});
}

ShapeType Ellipse::GetType()
{
    return type_;
}

double Ellipse::GetRadius()
{
    return radiusx_a_;
}

Helix::Helix(double x0, double y0, double r, double step) {
    center_.x = x0;
    center_.y = y0;
    radius_ = r;
    step_ = step;
}

Coordinate Helix::GetCoordinate(double parameter)
{
    double x = center_.x + radius_ + cos(parameter);
    double y = center_.y + radius_ + sin(parameter);
    double z = step_ * parameter;
    return Coordinate({x, y, z});
}

Vector Helix::GetFirstDerivate(double parameter) 
{
    double dx = -radius_ * sin(parameter);
    double dy =  radius_ * cos(parameter);
    return Vector({dx, dy, step_});
}

ShapeType Helix::GetType()
{
    return type_;
}

double Helix::GetRadius()
{
    return radius_;
}