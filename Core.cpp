#include <iostream>
#include <math.h>

#include <string>
#include <map>

#include "Geometry.hpp"

#include "DimensionPoint.cpp"
#include "Point.cpp"
#include "Angle.cpp"
#include "Box.cpp"
#include "Grid.cpp"
#include "Matrix.cpp"
using namespace scorpion::geometry;

template class Matrix<long double, 3u, 3u>;

#include "CollisionTree.cpp"
#include "AStarFinder.cpp"
#include "DimensionGrid.cpp"
#include "DimensionMap.cpp"
using namespace scorpion;

int main(int argc, char* argv[]){
    std::cout << "[INFO]: Application started...\n";//!Debugging
    //Angle<float, 3u> a = Angle<float, 3u>({20.0f, 20.0f, 1.0f}, {8.0f, 8.0f, 1.0f});
    //a.setDirection(false);
    //std::cout << "[INFO]: Angle: " << a << "\n";//!Debugging
    //Grid<float, 2u> grid_ = Grid<float, 2u>();
    //grid_.resizeTo(Box<float, 2u>({0.0f, 0.0f}, {55.0f, 75.0f}));
    //std::cout << "" << grid_ << "\n";
    //std::cout << "\n";
    //!Ill come back to muking with this angle shit soon...
    //Point<float, 2u> test_ = Point<float, 2u>({1.0f, 1.0f});
    //Shape<float, 2u> spe_ = Shape<float, 2u>();
    //spe_.addPoint({0.0f, 0.0f});
    //spe_.addPoint({2.0f, 0.0f});
    //spe_.addPoint({2.0f, 2.0f});
    //spe_.addPoint({0.0f, 2.0f});
    //std::cout << "Shape Contains Test Point(?): " << ((spe_.contains(test_)) ? "true" : "false") << "\n\n";
    //*
    Angle<float, 2u> a1_ = Angle<float, 2u>({-1.0f, 1.0f});
    Angle<float, 2u> a2_ = Angle<float, 2u>({-1.0f, -1.0f});
    Angle<float, 2u> d_ = Angle<float, 2u>::getDifference(a1_, a2_);
    std::cout << "[INFO]: Final Differential: " << d_ << "\n";//!Debugging//*/
    std::cout << "[INFO]: Application Terminated.\n";//!Debugging
    return(0);
}
