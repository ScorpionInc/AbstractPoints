/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: abstract class for manipulating data along multiple dimensions of many types
 * TODO:
 * #1) Create A TODO List
//*/
#include <iostream>

#include "Point.cpp"
using namespace scorpion::geometry;

#ifndef DIMENSIONSTORAGE_HPP_
#define DIMENSIONSTORAGE_HPP_

namespace scorpion{
    template<typename T, size_t dimensions>
    class DimensionStorage{
        public:
            DimensionStorage();
            ~DimensionStorage();
            virtual T at(Point<size_t, dimensions> index) = 0;
            virtual void set(Point<size_t, dimensions> index, T value) = 0;
            void shift();
        protected:
        private:
    };
}

#endif // DIMENSIONSTORAGE_HPP_
