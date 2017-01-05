/* Notes:
 * Version: 1.0.0.0
 * Author: SI
 * Purpose: A map of points in multiple dimensions and related data
 * Last Updated: 20151223
 * TODO:
 * 1) Make A TODO List...
//*/
#include <iostream>
#include <map>

#include "Point.cpp"
using namespace scorpion::geometry;

#ifndef DIMENSIONMAP_HPP_
#define DIMENSIONMAP_HPP_

namespace scorpion{
    template<typename T, size_t dimensions>
    class DimensionMap{
        public:
            DimensionMap();
            ~DimensionMap();
        protected:
        private:
    };
}

#endif // DIMENSIONMAP_HPP_
