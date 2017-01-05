/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: Abstract Point Class that supports operations over multiple dimensions.
 * Last Updated: 20160118
 * TODO:
 * 1) Make a TODO List
//*/

#include <iostream>
#include <string>
#include <math.h>

#include "DimensionPoint.cpp"

#ifndef POINT_HPP_
#define POINT_HPP_

namespace scorpion{
namespace geometry{
    template<typename T, size_t dimensions>
    class Point{
        public:
            static std::string getDefaultDimensionName(const size_t dimension_index);
            static Point<T, dimensions> getNormal(const Point<T, dimensions> &p_);//!TODO
            Point(T* collection[dimensions] = nullptr);
            Point(std::initializer_list<T> c);
            Point(const Point<T, dimensions>& p);//!COPY OVERLOAD
            ~Point();
            bool isWithin(const double distance, const Point<T, dimensions> p) const;
            bool isWithin(const float distance, const Point<T, dimensions> p) const;
            bool isWithin(const long double distance, const Point<T, dimensions> p) const;
            bool isWithin(const double distance, const Point<T, dimensions>* p) const;
            bool isWithin(const float distance, const Point<T, dimensions>* p) const;
            bool isWithin(const long double distance, const Point<T, dimensions>* p) const;
            bool normal() const;//!TODO
            Point<T, dimensions> getNormal();//!TODO
            static constexpr size_t DIMENSIONS_ = dimensions;
            static size_t getDimensions();
            double getMagnitude() const;//!TODO
            float getMagnitudeF() const;//!TODO
            long double getMagnitudeL() const;//!TODO
            double getDistance(const Point<T, dimensions> p) const;
            float getDistanceF(const Point<T, dimensions> p) const;
            long double getDistanceL(const Point<T, dimensions> p) const;
            double getDistance(const Point<T, dimensions>* p) const;
            float getDistanceF(const Point<T, dimensions>* p) const;
            long double getDistanceL(const Point<T, dimensions>* p) const;
            DimensionPoint<T>* getDimension(size_t dimension_index_) const;
            DimensionPoint<T>* getDimension(std::string dimension_name_) const;
            T getValue(const DimensionPoint<T>* dimension_) const;
            T getValue(const size_t dimension_index_) const;
            T getValue(const std::string dimension_name_) const;
            T dotProduct(Point<T, dimensions> p_) const;//!TODO
            std::string getDimensionName(const DimensionPoint<T>* dimension_) const;
            std::string getDimensionName(const size_t dimension_index_) const;
            void normalize();//!TODO
            void setValue(DimensionPoint<T>* dimension_, const T value);
            void setValue(const size_t dimension_index_, const T value);
            void setValue(const std::string dimension_name_, const T value);
            void setDimensionName(DimensionPoint<T>* dimension_, const std::string value);
            void setDimensionName(const size_t dimension_index_, const std::string value);
            void setDimensionName(const std::string dimension_name_, const std::string value);
            void debug(std::ostream* os_ = nullptr) const;//!Temporary(?)
            //Operator
            friend std::ostream& operator <<(std::ostream& os, const Point<T, dimensions>& point_){
                os << "(";
                for(size_t i = 0u; i < dimensions; i++){
                    os << point_.getValue(i);
                    if((i + 1) < dimensions)os << ", ";
                }
                os << ")";
                return(os);
            }
            bool operator != (const Point<T, dimensions> &p)const;
            bool operator == (const Point<T, dimensions> &p)const;
            bool operator <= (const Point<T, dimensions> &p)const;
            bool operator >= (const Point<T, dimensions> &p)const;
            bool operator < (const Point<T, dimensions> &p)const;
            bool operator > (const Point<T, dimensions> &p)const;
            Point<T, dimensions> operator + (const Point<T, dimensions> &p)const;
            Point<T, dimensions> operator - (const Point<T, dimensions> &p)const;
            Point<T, dimensions> operator * (const Point<T, dimensions> &p)const;
            Point<T, dimensions> operator / (const Point<T, dimensions> &p)const;
            Point<T, dimensions> operator + (const T &value)const;
            Point<T, dimensions> operator - (const T &value)const;
            Point<T, dimensions> operator * (const T &value)const;
            Point<T, dimensions> operator / (const T &value)const;
            void operator += (const Point<T, dimensions> &p);
            void operator -= (const Point<T, dimensions> &p);
            void operator *= (const Point<T, dimensions> &p);
            void operator /= (const Point<T, dimensions> &p);
            void operator += (const T &value);
            void operator -= (const T &value);
            void operator *= (const T &value);
            void operator /= (const T &value);
            Point<T, dimensions>& operator = (const Point<T, dimensions> &p);//!ASSIGNMENT OVERLOAD
        protected:
            DimensionPoint<T>* value;
        private:
    };
}
}

#endif // POINT_HPP_
