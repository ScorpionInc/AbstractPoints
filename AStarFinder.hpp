#include <iostream>
#include <vector>

#include "DimensionGrid.cpp"
using namespace scorpion;

#include "Point.cpp"
#include "Box.cpp"
using namespace scorpion::geometry;

#ifndef ASTARFINDER_HPP_
#define ASTARFINDER_HPP_

namespace scorpion{
    template<typename T, typename costType = size_t>
    class AStarFinder{
        public:
            struct AStarNode{
                Box<T, 2u> bounds;
                T cost = (T)0;
            };
            AStarFinder(Box<T, 2u> bounds, T node_size, Point<T, 2u> pos = Point<T, 2u>());
            ~AStarFinder();
            bool hasNext() const;
            bool inRange(Point<T, 2u> p) const;
            bool inRange(Box<T, 2u> box) const;
            bool inRange(size_t x, size_t y) const;
            T getWidth() const;
            T getHeight() const;
            T getNodeWidth() const;
            T getNodeHeight() const;
            size_t getCost(size_t x, size_t y) const;
            size_t getRowCount() const;
            size_t getColumnCount() const;
            Point<T, 2u> getPosition() const;
            Point<T, 2u> peek() const;
            Point<T, 2u> next() const;
            Point<T, 2u> target() const;
            Box<T, 2u> getBounds() const;
            AStarNode* getNode(size_t x, size_t y) volatile;
            bool calcPath(Point<T, 2u> target);
            bool calcPath(Point<T, 2u>* target);
            void init(Box<T, 2u> bounds, T node_size, Point<T, 2u> pos);
            void setPosition(Point<T, 2u> pos);
            void setCost(size_t x, size_t y, T cost);
            void setTouchingCost(Box<T, 2u> t_box, T cost);
            void setTouchingCost(Box<T, 2u>* t_box, T cost);
            void setContainingCost(Box<T, 2u> c_box, T cost);
            void setContainingCost(Box<T, 2u>* c_box, T cost);
            void optimizePath();
        protected:
            Point<T, 2u> position;
            Box<T, 2u> bounds;//!May be unneeded
            T nodeSize;//!Maybe unneeded
            DimensionGrid<Box<T, 2u>, size_t, 2u> nodes_;
        private:
    };
}

#endif // ASTARFINDER_HPP_
