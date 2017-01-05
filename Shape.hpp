/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: Abstract collection of points to form generic shapes...
 * Created: 20151224
 * Last Updated: 20151224
 * TODO:
 * 1) Make a TODO List...
//*/
#include <iostream>
#include <vector>
#include <string>

#include "Point.cpp"
#include "Angle.cpp"

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

namespace scorpion{
namespace geometry{
    template<typename T, size_t dimensions>
    class Shape{
    public:
        Shape();
        Shape(const std::vector<Point<T, dimensions> > &buffer_);
        ~Shape();
        bool isConcave() const;
        bool isConvex() const;
        bool hasOverlaps() const;
        bool isValid() const;
        bool contains(const Point<T, dimensions> &point_) const;
        bool contains(const Shape<T, dimensions> &shape_) const;
        bool touchs(const Shape<T, dimensions> &shape_) const;
        bool hasPoint(const Point<T, dimensions> &point_) const;
        bool hasPoint(const std::initializer_list<T> c_) const;
        size_t pointCount() const;
        T getDimensionLargest(const std::string name_) const;
        T getDimensionLargest(const size_t index_) const;
        T getDimensionSmallest(const std::string name_) const;
        T getDimensionSmallest(const size_t index_) const;
        Point<T, dimensions> getMaximumPoint() const;
        Point<T, dimensions> getMinimumPoint() const;
        Point<T, dimensions> getCenterOfMass() const;
        Point<T, dimensions> getPoint(const size_t index_) const;
        void getPoints(std::vector<Point<T, dimensions> > &buffer_) const;
        void getNearestPoints(std::vector<size_t> &index_buffer_, const Point<T, dimensions> &target_, bool cull = true) const;
        void getNearPoints(std::vector<size_t> &index_buffer_, const Point<T, dimensions> &target_, size_t maximum_, size_t minimum_ = 1u) const;
        void getPointsWithin(std::vector<size_t> &index_buffer_, const Point<T, dimensions> &target_, T distance_) const;
        void addPoint(const Point<T, dimensions> &point_);
        void addPoint(const std::initializer_list<T> c_);
        void removePoint(const size_t index_);
        void removePoint(const Point<T, dimensions> &point_);
        void removePoint(const std::initializer_list<T> c_);
        void reorderPoints();//!Self Heal
        void clearPoints();
    protected:
        std::vector<Point<T, dimensions> > points_;
    private:
    };
}
}

#endif // SHAPE_HPP_
