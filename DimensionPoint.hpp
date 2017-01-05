/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: A Container Class for associating a name with a dimension value.
 * Last Updated: 20151223
 * TODO:
 * 1) Make a TODO List...
//*/

#include <string>
#include <iostream>

#ifndef DIMENSIONPOINT_HPP_
#define DIMENSIONPOINT_HPP_

namespace scorpion{
namespace geometry{
    template<typename T>
    class DimensionPoint{
        public:
            T value;
            DimensionPoint(T value_ = (T)0, std::string dimensionName = "");
            ~DimensionPoint();
            bool hasName() const;
            std::string getName() const;
            void setName(const std::string name);
            void debug(std::ostream* os_ = nullptr) const;//!Temporary(?)
            //Operators
            friend std::ostream& operator <<(std::ostream& os, const DimensionPoint<T>& point_){
                if(point_.hasName())os << point_.getName().c_str() << ":";
                os << point_.value;
                return(os);
            }
            bool operator == (const DimensionPoint<T> &p) const;
            bool operator != (const DimensionPoint<T> &p) const;
            bool operator <= (const DimensionPoint<T> &p) const;
            bool operator >= (const DimensionPoint<T> &p) const;
            bool operator < (const DimensionPoint<T> &p) const;
            bool operator > (const DimensionPoint<T> &p) const;
            void operator += (const DimensionPoint<T> &p);
            void operator += (const T &value);
            void operator -= (const DimensionPoint<T> &p);
            void operator -= (const T &value);
        protected:
            std::string name_;
        private:
    };
}
}

#endif // DIMENSIONPOINT_HPP_
