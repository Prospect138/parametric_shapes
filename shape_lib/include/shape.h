#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <iostream>

struct Coordinate {
    double x;
    double y;
    double z;
};

std::ostream& operator<<(std::ostream& out, const Coordinate& coordinate);

struct Vector {
    double i;
    double j;
    double k;
};

std::ostream& operator<<(std::ostream& out, const Vector& vector);

enum class ShapeType {
    CIRCLE,
    ELLIPSE,
    HELIX
};

std::ostream& operator<<(std::ostream& out, const ShapeType& type);

//- All curves are parametrically defined, i.e. a point is calculated using some C(t) formula
class Shape {
public:
    virtual Coordinate GetCoordinate(double parameter) = 0;
    virtual Vector GetFirstDerivate(double parameter) = 0;
    virtual ShapeType GetType() = 0 ;
    virtual double GetRadius() = 0;
};

//- Circle is planar in the plane XoY (i.e. all Z-coordinates are 0) and is defined by its radius.
class Circle : public Shape {
public:
    Circle() = default;
    Circle(double x0, double y0, double radius);
    Coordinate GetCoordinate(double parameter) override;
    Vector GetFirstDerivate(double parameter) override;
    ShapeType GetType() override;
    double GetRadius() override;

private:
    ShapeType type_ = ShapeType::CIRCLE;
    Coordinate center_;
    double radius_;
};

//- Ellipse is planar in the plane XoY and is defined by its two radii, along X and Y axes
class Ellipse : public Shape {
public:
    Ellipse() = default;
    Ellipse(double x0, double y0, double rad1, double rad2);
    Coordinate GetCoordinate(double parameter) override;
    Vector GetFirstDerivate(double parameter) override;
    ShapeType GetType() override;
    double GetRadius() override;

private:
    ShapeType type_ = ShapeType::ELLIPSE;
    Coordinate center_;
    double radiusx_a_;
    double radiusy_b_;
};

//Helix is spatial and is defined by its radius and step. It takes 2 * PI in
//parametric space to make a round, i.e. any point on helix satisfies the condition C(t + 2*PI) = C(t) +
//{0, 0, step}.
class Helix : public Shape {
public:
    Helix() = default;
    Helix(double x0, double y0, double r, double step);
    Coordinate GetCoordinate(double parameter) override;
    Vector GetFirstDerivate(double parameter) override;
    ShapeType GetType() override;
    double GetRadius() override;

private:
    ShapeType type_ = ShapeType::HELIX;
    Coordinate center_;
    double radius_;
    double step_;
};