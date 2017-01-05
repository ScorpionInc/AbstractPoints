/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: A vector of points in multiple dimensions and related data
 * Last Updated: 20151223
 * TODO:
 * 1) Make DimensionGrid a child of the Grid Superclass...
//*/
#include <iostream>
#include <vector>

#include "Point.cpp"
#include "Box.cpp"
#include "Grid.cpp"

#ifndef DIMENSIONGRID_HPP_
#define DIMENSIONGRID_HPP_

namespace scorpion{
    template<typename T, typename S, size_t dimensions>//!DataType, SizeType, Dimensions
    class DimensionGrid{
        public:
            struct GRID_ITEM{
                T value;
                Box<S, dimensions> bounds;//!Replace with index(?)
            };
            DimensionGrid(Point<S, dimensions> size_, S nodeSize);
            ~DimensionGrid();
            //bool inRange(const Point<size_t, dimensions> index)const;
            //bool inBounds(const Point<S, dimensions> p)const;
            //Point<size_t, dimensions> getIndex(const Point<S, dimensions> target)const;
            GRID_ITEM getNode(const Point<size_t, dimensions> index);
            Point<size_t, dimensions> find(const T target, const Point<size_t, dimensions> start_ = Point<size_t, dimensions>())const;
            T at(const Point<size_t, dimensions> p)const;
            T atNearest(const Point<S, dimensions> p)const;
            S getDimensionSize(size_t dimension_index) const;
            Point<size_t, dimensions> getNextIndex(Point<size_t, dimensions> s_point, Point<size_t, dimensions> changeOf, bool makeSafe = true);//getNextSafe
            Point<size_t, dimensions> getNextIndex(Point<size_t, dimensions> s_point, Point<size_t, dimensions>* changeOf, bool makeSafe = true);//getNextSafe
            Point<S, dimensions> getNextPoint(Point<S, dimensions> s_point, Point<S, dimensions> changeOf, bool makeSafe = true);//getNextSafe
            Point<S, dimensions> getNextPoint(Point<S, dimensions> s_point, Point<S, dimensions>* changeOf, bool makeSafe = true);//getNextSafe
            size_t getNodeCount(const size_t dimension_index) const;
            Point<size_t, dimensions> getNodeSizes() const;//getCount
            Point<S, dimensions> getDimensionSizes() const;//getWidth
            void shift(Point<size_t, dimensions> index, std::string dimensionName, size_t amount = 1u);//size_t blockSize = 1u
            void shift(Point<size_t, dimensions> index, size_t dimensionIndex, size_t amount = 1u);//size_t blockSize = 1u
            void shift(Point<size_t, dimensions> index, size_t blockSize, std::string dimensionName, size_t amount = 1u);
            void shift(Point<size_t, dimensions> index, size_t blockSize, size_t dimensionIndex, size_t amount = 1u);
            void shift(Point<size_t, dimensions> index, Point<S, dimensions> changeOf, size_t amount = 1u);//size_t blockSize = 1u
            void shift(Point<size_t, dimensions> index, Point<S, dimensions>* changeOf, size_t amount = 1u);//size_t blockSize = 1u
            void shift(Point<size_t, dimensions> index, size_t blockSize, Point<S, dimensions> changeOf, size_t amount = 1u);
            void shift(Point<size_t, dimensions> index, size_t blockSize, Point<S, dimensions>* changeOf, size_t amount = 1u);
            void roll(std::string dimensionName, S amount = (S)1);
            void roll(size_t dimensionIndex, S amount = (S)1);
            void roll(Point<size_t, dimensions> changeOf, S amount = (S)1);
            void roll(Point<size_t, dimensions>* changeOf, S amount = (S)1);
            void insert(std::string dimensionName, size_t index, T dvalue = (T)0);
            void insert(size_t dimensionIndex, size_t index, T dvalue = (T)0);
            void clear();
            void set(Point<S, dimensions> P, T value);
            void set(Box<S, dimensions> range, T value);
            void init(const Point<S, dimensions> size_, const S nodeSize);
            void debug(std::ostream* os_ = nullptr)const;//!Temporary(?)
            //Operators
        protected:
            Point<S, dimensions> size_;
            void* data_;
        private:
    };
}

#endif // DIMENSIONGRID_HPP_
