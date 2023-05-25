#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>

#include "shape.h"

//Populate a container (e.g. vector or list) of objects of these types created in random manner with
//random parameters.
void PopulateVector(std::vector<std::shared_ptr<Shape>> &vec) 
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<> num_of_elements(5, 50);
    std::uniform_int_distribution<> tp(0, 2);
    std::uniform_int_distribution<> cnt(-10, 10);
    std::uniform_int_distribution<> rad(1, 20);
    std::uniform_int_distribution<> stp(1, 5);
    
    for (int i = 0; i < num_of_elements(generator); ++i){
        int type = tp(generator);
        if (type == 0){
            double x0 = cnt(generator);
            double y0 = cnt(generator);
            double r = rad(generator);

            Circle circle0(x0, y0, r);
            std::shared_ptr<Circle> circle = std::make_shared<Circle>(circle0);
            vec.push_back(std::move(circle));
        }
        if (type == 1){
            double x0 = cnt(generator);
            double y0 = cnt(generator);
            double r1 = rad(generator);            
            double r2 = rad(generator);

            Ellipse ellipse0(x0, y0, r1, r2);
            std::shared_ptr<Ellipse> ellipse = std::make_shared<Ellipse>(ellipse0);
            vec.push_back(std::move(ellipse));
        }
        if (type == 2){
            double x0 = cnt(generator);
            double y0 = cnt(generator);
            double r = rad(generator);  
            double step = stp(generator);

            Helix helix0(x0, y0, r, step);
            std::shared_ptr<Helix> helix = std::make_shared<Helix>(helix0);
            vec.push_back(std::move(helix));
        }
    }
}

//Print coordinates of points and derivatives of all curves in the container at t=PI/4.
void PrintCoordiatesAndDerivates(const std::vector<std::shared_ptr<Shape>>& vec, double parameter)
{
    for (int i = 0; i < vec.size(); ++i){
        std::cout << std::setprecision(4);
        std::cout << "Shape " << i << ": \t" << vec[i] ->GetType() << "\tcoords: \t" << vec[i] -> GetCoordinate(parameter) << "\n"
        << "\t\t\tderivate: \t" <<vec[i] -> GetFirstDerivate(parameter) << "\n";
    }
}

//Populate a second container that would contain only circles from the first container. Make sure the
//second container shares (i.e. not clones) circles of the first one, e.g. via pointers.
std::vector<std::shared_ptr<Shape>> MakeCircleClones(const std::vector<std::shared_ptr<Shape>>& original_vec)
{
    std::vector<std::shared_ptr<Shape>> circle_clones;
    for (const auto& item : original_vec){
        if (item -> GetType() == ShapeType::CIRCLE) {
            circle_clones.push_back(item);
        }
    }
    return circle_clones;
}

//Sort the second container in the ascending order of circles’ radii. That is, the first element has the
//smallest radius, the last - the greatest.
void SortCircleCopies(std::vector<std::shared_ptr<Shape>>& vec) 
{
    std::sort(vec.begin(), vec.end(), [](const std::shared_ptr<Shape>& lhs, const std::shared_ptr<Shape>& rhs){
        return lhs -> GetRadius() < rhs -> GetRadius();
    });
}

//Compute the total sum of radii of all curves in the second container.
double ComputeRadiusSums(const std::vector<std::shared_ptr<Shape>>& vec)
{
    double total = 0.0;
    for (const auto& item : vec){
        //std::cout << item -> GetRadius() << std::endl;
        total += item -> GetRadius();
    } 
    return total;
}

int main() {
    std::vector<std::shared_ptr<Shape>> vec;
    PopulateVector(vec);
    PrintCoordiatesAndDerivates(vec, M_PI/4);
    std::vector<std::shared_ptr<Shape>> circle_clones = MakeCircleClones(vec);
    SortCircleCopies(circle_clones);
    double i = ComputeRadiusSums(circle_clones);
    std::cout << "Total sum of all circles radii: " << i << "\n";
}