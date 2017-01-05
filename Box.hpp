/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: An abstract box class
 * Last Updated: 20151224
 * TODO:
 * 1) Create a TODO List
//*/

#include <iostream>
#include <math.h>
#include "Point.cpp"

#ifndef BOX_HPP_
#define BOX_HPP_

typedef unsigned int size_t;
namespace scorpion{
namespace geometry{
    template<typename T, size_t dimensions>
    class Box{
        public:
            Box(T* collection1[dimensions] = nullptr, T* collection2[dimensions] = nullptr);
            Box(Point<T, dimensions> p1, Point<T, dimensions> p2);
            Box(std::initializer_list<T> c);
            Box(std::initializer_list<T> c1, std::initializer_list<T> c2);
            ~Box();
            bool isSquare() const;
            bool touchs(const Box<T, dimensions> box_) const;
            bool touchs(const Box<T, dimensions>* box_) const;
            bool contains(const Point<T, dimensions> p_) const;
            bool contains(const Point<T, dimensions>* p_) const;
            bool contains(const Box<T, dimensions> box_) const;
            bool contains(const Box<T, dimensions>* box_) const;
            size_t getDimensions() const;
            T getDimensionLargest(const std::string dimensionName) const;
            T getDimensionLargest(const size_t dimension_index_) const;
            T getDimensionSmallest(const std::string dimensionName) const;
            T getDimensionSmallest(const size_t dimension_index_) const;
            T getDimensionSize(const std::string dimensionName) const;
            T getDimensionSize(const size_t dimension_index) const;
            Point<T, dimensions> getSize() const;
            Point<T, dimensions> getCenter() const;
            Point<T, dimensions> getLargestDimensionPoint() const;
            Point<T, dimensions> getSmallestDimensionPoint() const;
            Point<T, dimensions> getNext(const Point<T, dimensions> current_, const Point<T, dimensions> changeOf_, const bool makeSafe = true) const;
            Box<T, dimensions> getOverlap(Box<T, dimensions> box_) const;
            Box<T, dimensions> getOverlap(Box<T, dimensions>* box_) const;
            void setDimensionSmallest(const size_t dimension_index, const T value);
            void setDimensionSmallest(const std::string dimensionName, const T value);
            void setDimensionLargest(const size_t dimension_index, const T value);
            void setDimensionLargest(const std::string dimensionName, const T value);
            void shift(Point<T, dimensions> p_);
            void shift(Point<T, dimensions>* p_);
            void scale(Point<T, dimensions> p_);
            void scale(Point<T, dimensions>* p_);//!TODO
            void debug(std::ostream* os_ = nullptr) const;//!Temporary(?)
            //Operator(s)
            friend std::ostream& operator <<(std::ostream& os, const Box<T, dimensions>& box_){
                os << "{";
                os << "" << box_.getSmallestDimensionPoint() << " -> " << box_.getLargestDimensionPoint() << "";
                os << "}";
                return(os);
            }
            bool operator != (const Box<T, dimensions> &p) const;
            bool operator == (const Box<T, dimensions> &p) const;
            void operator += (const Box<T, dimensions> &p);
            void operator += (const T &value);
            void operator -= (const Box<T, dimensions> &p);
            void operator -= (const T &value);
        protected:
            Point<T, dimensions> p1;
            Point<T, dimensions> p2;
        private:
    };
    /*
    template<typename T>
    class Box_2D : scorpion::geometry::Box<T, 2u>{
        public:
            Box_2D();
            ~Box_2D();
            T getSurfaceArea();
        protected:
        private:
    };
    template<typename T>
    class Box_3D : scorpion::geometry::Box<T, 3u>{
        public:
            Box_3D();
            ~Box_3D();
            T getSurfaceArea();
            T getVolume();
        protected:
        private:
    };
    //*/
}
}

#endif // BOX_HPP_
