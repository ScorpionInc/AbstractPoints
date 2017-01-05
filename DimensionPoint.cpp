#include "DimensionPoint.hpp"
using namespace scorpion::geometry;

#ifndef DIMENSIONPOINT_CPP_
#define DIMENSIONPOINT_CPP_

//Variables

//Constructors
template<typename T>
DimensionPoint<T>::DimensionPoint(T value_, std::string dimensionName) : value(value_), name_(){
    this->setName(dimensionName);
}
template<typename T>
DimensionPoint<T>::~DimensionPoint(){}

//Functions
template<typename T>
bool DimensionPoint<T>::hasName() const{
    return(!this->name_.empty());
}
template<typename T>
std::string DimensionPoint<T>::getName() const{
    return(this->name_);
}

//Methods
template<typename T>
void DimensionPoint<T>::setName(const std::string name){
    this->name_ = name;
}
template<typename T>
void DimensionPoint<T>::debug(std::ostream* os_) const{
    if(os_ == nullptr)os_ = (std::ostream*)(&std::cout);
    (*os_) << "[INFO]: Debugging Dimension Point @ " << (this) << "\n";//!Debugging
    (*os_) << "[INFO]: Dimension has Name: " << ((this->hasName()) ? "true" : "false") << "\n";//!Debugging
    (*os_) << "[INFO]: Dimension Name: " << ((this->hasName()) ? this->name_.c_str() : "NONE/NULL") << "\t Dimension Value: " << this->value << "\n";//!Debugging
    (*os_) << "[INFO]: Finished Debugging Dimension Point @ " << (this) << "\n";//!Debugging
}

//Operators
template<typename T>
bool DimensionPoint<T>::operator == (const DimensionPoint<T> &p) const{
    return(this->getName() == p.getName() && this->value == p.value);
}
template<typename T>
bool DimensionPoint<T>::operator != (const DimensionPoint<T> &p) const{
    return(this->getName() != p.getName() || this->value != p.value);
}
template<typename T>
bool DimensionPoint<T>::operator <= (const DimensionPoint<T> &p) const{
    return(this->value <= p.value);
}
template<typename T>
bool DimensionPoint<T>::operator >= (const DimensionPoint<T> &p) const{
    return(this->value >= p.value);
}
template<typename T>
bool DimensionPoint<T>::operator < (const DimensionPoint<T> &p) const{
    return(this->value < p.value);
}
template<typename T>
bool DimensionPoint<T>::operator > (const DimensionPoint<T> &p) const{
    return(this->value > p.value);
}
template<typename T>
void DimensionPoint<T>::operator += (const DimensionPoint<T> &p){
    this->value += p.value;
}
template<typename T>
void DimensionPoint<T>::operator += (const T &v){
    this->value += v;
}
template<typename T>
void DimensionPoint<T>::operator -= (const DimensionPoint<T> &p){
    this->value -= p.value;
}
template<typename T>
void DimensionPoint<T>::operator -= (const T &v){
    this->value -= v;
}

#endif // DIMENSIONPOINT_CPP_
