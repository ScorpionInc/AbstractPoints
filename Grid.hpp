/* Notes:
 * Version: 1.0.0.0
 * Authors: Scorpion Inc
 * Purpose: Collection of same sized nodes of multiple dimensions; does not store extra data...
 * Last Updated: 20151224
 * TODO:
 * #1) Make a TODO list
//*/
#include <iostream>
#include <string>
#include <math.h>

#include "Point.hpp"
#include "Box.hpp"

#ifndef GRID_HPP_
#define GRID_HPP_

namespace scorpion{
namespace geometry{
    template<typename T, size_t dimensions>
    class Grid{
        public:
            Grid(Box<T, dimensions> bounds = Box<T, dimensions>(), Point<size_t, dimensions> nodeCount = Point<size_t, dimensions>());
            Grid(Point<T, dimensions> nodeSize, Point<size_t, dimensions> nodeCount);
            ~Grid();
            bool inRange(const Point<T, dimensions> point_) const;
            bool hasIndex(const Point<size_t, dimensions> index_) const;
            Box<T, dimensions> getBounds() const;
            Point<T, dimensions> getNodeSize() const;
            Point<size_t, dimensions> getCounts() const;
            size_t getCount(const size_t dimension_index) const;
            size_t getCount(const std::string dimension_name) const;
            Point<size_t, dimensions> getIndex(const Point<T, dimensions> point_) const;
            Point<T, dimensions> getPoint(const Point<size_t, dimensions> index_) const;
            Point<size_t, dimensions> getNextIndex(const Point<size_t, dimensions> current_, const Point<size_t, dimensions> changeOf_, const bool makeSafe = true) const;
            Point<T, dimensions> getNextPoint(const Point<T, dimensions> current_, const Point<T, dimensions> changeOf_, const bool makeSafe = true) const;
            void init(const Box<T, dimensions> bounds, const Point<size_t, dimensions> nodeCount);
            void init(const Point<T, dimensions> nodeSize, const Point<size_t, dimensions> nodeCount);
            void resizeTo(const Box<T, dimensions> bounds);
            void setPartsTo(const Point<size_t, dimensions> nodeCount);
            void setNodeSize(const Point<T, dimensions> nodeSize);
            void debug(std::ostream* os_) const;//!Temporary(?)
            //Operators
            friend std::ostream& operator <<(std::ostream& os, const Grid<T, dimensions>& grid_){
                //!TODO
                os << "{" << grid_.bounds << ", " << grid_.nodeCount << "}";
                return(os);
            }
        protected:
            Box<T, dimensions> bounds;//! x, y, is point of Grid, w, h, is the grid dimensions
            Point<size_t, dimensions> nodeCount;//! How many nodes compose the grid
        private:
    };
}
}

#endif // GRID_HPP_
