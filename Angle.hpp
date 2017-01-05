/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: Abstract Class for managing anglular direction in multiple dimensions
 * Created: 20151223
 * Last Updated: 20160520
 * TODO:
 * 1) Make A TODO List...
//*/
#include <iostream>
#include <string>
#include <cmath>//!Adds Support for long doubles
//#include <math.h>

#include "Point.hpp"

#ifndef ANGLE_HPP_
#define ANGLE_HPP_

namespace scorpion{
namespace geometry{
    template<typename T, size_t dimensions>
    class Angle{
    public:
        Angle(std::initializer_list<T> c = {});
        Angle(const Point<T, dimensions> &target);
        Angle(const Point<T, dimensions> &origin, const Point<T, dimensions> &target);
        ~Angle();
        static constexpr const char* DEGREE_SYMBOL = static_cast<const char*>("°\0");
        static constexpr const long double PI = static_cast<long double>(3.141592653589793);//!Max Percision 15 places (Float has 7)
        static constexpr const long double HALF_PI = Angle::PI / static_cast<long double>(2.0);//!Max Percision 15 places
        static constexpr const long double TWO_PI = Angle::PI * static_cast<long double>(2.0);//!Max Percision 15 places
        static constexpr const size_t DIMENSIONS_ = dimensions;
        static size_t getDimensions();
        static constexpr long double toDegrees(const long double &radians_){
            //! 1 PI = 180 degrees
            return((radians_ * static_cast<long double>(180)) / Angle::PI);
        }
        static constexpr long double toRadians(const long double &degrees_){
            return((degrees_ * Angle::PI) / static_cast<long double>(180));
        }
        static constexpr Angle<T, dimensions> getRedirected(const Angle<T, dimensions> &a_, bool clockwise){
            Point<T, dimensions> np_ = a_.getUnitValue();
            for(size_t i = 0u; i < dimensions; i++)
                if((clockwise && np_.getValue(i) > static_cast<T>(0)) || (!clockwise && np_.getValue(i) < static_cast<T>(0)))
                    np_.setValue(i, np_.getValue(i) * static_cast<T>(-1));
            return(Angle<T, dimensions>(np_));
        }
        static Angle<T, dimensions> getDifference(const Angle<T, dimensions> &a1_, const Angle<T, dimensions> &a2_);//!TODO
        T getDimensionChange(const size_t index_) const;
        Point<T, dimensions> getUnitValue() const;
        Point<T, dimensions> atDistance(T distance_) const;
        Angle<T, dimensions> getInverse() const;
        long double getDegrees(const size_t base_axis_index_, const size_t other_axis_index_) const;
        long double getRadians(const size_t base_axis_index_, const size_t other_axis_index_) const;
        long double getDegrees(const std::string base_axis_name_, const std::string other_axis_name_) const;
        long double getRadians(const std::string base_axis_name_, const std::string other_axis_name_) const;
        void setTo(const Point<T, dimensions> &target);
        void setTo(const Point<T, dimensions> &origin, const Point<T, dimensions> &target);
        void setDirection(const bool clockwise);
        void invert();
        //Operators
        friend std::ostream& operator <<(std::ostream& os, const Angle<T, dimensions>& angle_){
            os << "" << angle_.angles_ << "";
            for(size_t i = 1u; i < dimensions; i++)
                os << "[" << (i - 1u) << "->" << i << "]: " << angle_.getRadians((i - 1u), i) << ":" << angle_.getDegrees((i - 1u), i) << Angle::DEGREE_SYMBOL << " ";
            return(os);
        }
        bool operator != (const Angle<T, dimensions> &a)const;
        bool operator == (const Angle<T, dimensions> &a)const;
        bool operator <= (const Angle<T, dimensions> &a)const;
        bool operator >= (const Angle<T, dimensions> &a)const;
        bool operator < (const Angle<T, dimensions> &a)const;
        bool operator > (const Angle<T, dimensions> &a)const;
        Angle<T, dimensions> operator + (const Angle<T, dimensions> &a)const;
        Angle<T, dimensions> operator - (const Angle<T, dimensions> &a)const;
        Angle<T, dimensions> operator * (const Angle<T, dimensions> &a)const;
        Angle<T, dimensions> operator / (const Angle<T, dimensions> &a)const;
        Angle<T, dimensions> operator + (const T &value)const;
        Angle<T, dimensions> operator - (const T &value)const;
        Angle<T, dimensions> operator * (const T &value)const;
        Angle<T, dimensions> operator / (const T &value)const;
        void operator += (const Angle<T, dimensions> &a);
        void operator -= (const Angle<T, dimensions> &a);
        void operator *= (const Angle<T, dimensions> &a);
        void operator /= (const Angle<T, dimensions> &a);
        void operator += (const T &value);
        void operator -= (const T &value);
        void operator *= (const T &value);
        void operator /= (const T &value);
    protected:
        Point<T, dimensions> angles_;
        void simplify();
    private:
    };
}
}

#endif // ANGLE_HPP_
