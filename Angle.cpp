#include "Angle.hpp"
using namespace scorpion::geometry;

#ifndef ANGLE_CPP_
#define ANGLE_CPP_

//Variables

//Constructors
template<typename T, size_t dimensions>
Angle<T, dimensions>::Angle(std::initializer_list<T> c) : angles_(){
    for(size_t i = 0u; i < dimensions; i++){
        if(i >= c.size())break;
        this->angles_.setValue(i, (T)(*(c.begin() + i)));
    }
    this->simplify();
}
template<typename T, size_t dimensions>
Angle<T, dimensions>::Angle(const Point<T, dimensions> &a) : angles_(){
    this->setTo(a);
}
template<typename T, size_t dimensions>
Angle<T, dimensions>::Angle(const Point<T, dimensions> &a, const Point<T, dimensions> &b) : angles_(){
    this->setTo(a, b);
}
template<typename T, size_t dimensions>
Angle<T, dimensions>::~Angle(){}

//Functions
template<typename T, size_t dimensions>
size_t Angle<T, dimensions>::getDimensions(){
    return(dimensions);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::getDifference(const Angle<T, dimensions> &a1_, const Angle<T, dimensions> &a2_){
    //!TODO
    Point<T, dimensions> ncoa = Point<T, dimensions>();
    if(a1_.getInverse() == a2_){
        return(Angle<T,dimensions>({cos(Angle::PI), sin(Angle::PI)}));
    }
    size_t next_index_ = static_cast<size_t>(0u);
    size_t angular_cnt = static_cast<size_t>(ceilf(static_cast<float>(dimensions) / 2.0f)) + 1u;
    if(dimensions <= 1u)angular_cnt = 0u;
    long double deltas_[angular_cnt];
    long double d1_, d2_;
    std::cout << "[INFO]: A1_: " << a1_ << " - A2_: " << a2_ << "\n";//!Debugging
    std::cout << "[INFO]: Angular Count: " << angular_cnt << "\n";//!Debugging
    for(size_t i = 1u; i < dimensions + 1u; i += 1u){
        next_index_ = (i < dimensions ? i : 0u);
        std::cout << "[INFO]: Calculating delta of dimensions: " << i - 1u << " -> " << next_index_ << "\n";//!Debugging
        d1_ = (a1_.getRadians(i - 1u, next_index_) < 0.0 ? a1_.getRadians(i - 1u, next_index_)  + Angle::PI : a1_.getRadians(i - 1u, next_index_));
        d2_ = (a2_.getRadians(i - 1u, next_index_) < 0.0 ? a2_.getRadians(i - 1u, next_index_) + Angle::PI : a2_.getRadians(i - 1u, next_index_));
        deltas_[i - 1u] = (d2_ - d1_);
        //deltas_[i - 1u] = abs(a2_.getRadians(i - 1u, i)) - abs(a1_.getRadians(i - 1u, i));
        std::cout << "[INFO]: A1.r: " << a1_.getRadians(i - 1u, next_index_) << " A2.r: " << a2_.getRadians(i - 1u, next_index_) << " Diff: " << deltas_[i - 1u] << "\n";//!Debugging
    }
    for(size_t i = 0u; i < angular_cnt; i++){
        next_index_ = (i == 0u ? angular_cnt - 1u : i - 1u);
        ncoa.setValue(i, (cos(deltas_[i]) * sin(deltas_[next_index_])));
    }
    std::cout << "[INFO]: NCOA: " << ncoa << "\n";//!Debugging
    return(Angle<T,dimensions>({static_cast<T>(cos(deltas_[0u])), static_cast<T>(sin(deltas_[0u]))}));
    //return(Angle<T,dimensions>(ncoa));
}
template<typename T, size_t dimensions>
T Angle<T, dimensions>::getDimensionChange(const size_t index_) const{
    return(this->angles_.getValue(index_));
}
template<typename T, size_t dimensions>
Point<T, dimensions> Angle<T, dimensions>::getUnitValue() const{
    return(this->angles_);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Angle<T, dimensions>::atDistance(T distance_) const{
    return(this->angles_ * distance_);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::getInverse() const{
    return((*this) * static_cast<T>(-1));
}
template<typename T, size_t dimensions>
long double Angle<T, dimensions>::getDegrees(const size_t base_axis_index_, const size_t other_axis_index_) const{
    return(Angle::toDegrees(this->getRadians(base_axis_index_, other_axis_index_)));
}
template<typename T, size_t dimensions>
long double Angle<T, dimensions>::getRadians(const size_t base_axis_index_, const size_t other_axis_index_) const{
    return(atan2(this->angles_.getValue(other_axis_index_), this->angles_.getValue(base_axis_index_)));
}
template<typename T, size_t dimensions>
long double Angle<T, dimensions>::getDegrees(const std::string base_axis_name_, const std::string other_axis_name_) const{
    return(Angle::toDegrees(this->getRadians(base_axis_name_, other_axis_name_)));
}
template<typename T, size_t dimensions>
long double Angle<T, dimensions>::getRadians(const std::string base_axis_name_, const std::string other_axis_name_) const{
    return(atan2(this->angles_.getValue(other_axis_name_), this->angles_.getValue(base_axis_name_)));
}

//Methods
template<typename T, size_t dimensions>
void Angle<T, dimensions>::setTo(const Point<T, dimensions> &a){
    this->setTo(Point<T, dimensions>(), a);
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::setTo(const Point<T, dimensions> &a, const Point<T, dimensions> &b){
    this->angles_ = (b - a);
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::setDirection(const bool clockwise){
    //Set change of angle direction to either positive or negative value
    for(size_t i = 0u; i < dimensions; i++)
        if((clockwise && this->angles_.getValue(i) > static_cast<T>(0)) || (!clockwise && this->angles_.getValue(i) < static_cast<T>(0)))
            this->angles_.setValue(i, this->angles_.getValue(i) * static_cast<T>(-1));
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::invert(){
    this->angles_ *= static_cast<T>(-1);
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::simplify(){
    if(dimensions < 1u)return;
    T deltaExtreme = static_cast<T>(0);
    if(this->angles_.getValue(0u) >= static_cast<T>(0)){
        deltaExtreme = this->angles_.getValue(0u);
    } else {
        deltaExtreme = (this->angles_.getValue(0u) * static_cast<T>(-1));
    }
    for(size_t i = 1u; i < dimensions; i++){
        if(this->angles_.getValue(i) >= static_cast<T>(0)){
            if(this->angles_.getValue(i) > deltaExtreme)deltaExtreme = this->angles_.getValue(i);
        }else{
            if((this->angles_.getValue(i) * static_cast<T>(-1)) > deltaExtreme)deltaExtreme = (this->angles_.getValue(i) * static_cast<T>(-1));
        }
    }
    std::cout << "[INFO]: Delta Extreme: " << deltaExtreme << "!\n";//!Debugging
    if(deltaExtreme != static_cast<T>(0))
    //if(deltaExtreme > static_cast<T>(1))
    this->angles_ /= deltaExtreme;
}

//Operators
template<typename T, size_t dimensions>
bool Angle<T, dimensions>::operator != (const Angle<T, dimensions> &p)const{
    return(!(*this == p));
}
template<typename T, size_t dimensions>
bool Angle<T, dimensions>::operator == (const Angle<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->angles_.getValue(i) != p.getDimensionChange(i))return(false);
    return(true);
}
template<typename T, size_t dimensions>
bool Angle<T, dimensions>::operator <= (const Angle<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->angles_.getValue(i) > p.getDimensionChange(i))return(false);
    return(true);
}
template<typename T, size_t dimensions>
bool Angle<T, dimensions>::operator >= (const Angle<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->angles_.getValue(i) < p.getDimensionChange(i))return(false);
    return(true);
}
template<typename T, size_t dimensions>
bool Angle<T, dimensions>::operator < (const Angle<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->angles_.getValue(i) >= p.getDimensionChange(i))return(false);
    return(true);
}
template<typename T, size_t dimensions>
bool Angle<T, dimensions>::operator > (const Angle<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->angles_.getValue(i) <= p.getDimensionChange(i))return(false);
    return(true);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator + (const Angle<T, dimensions> &p)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ + p.getUnitValue());
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator - (const Angle<T, dimensions> &p)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ - p.getUnitValue());
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator * (const Angle<T, dimensions> &p)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ * p.getUnitValue());
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator / (const Angle<T, dimensions> &p)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ / p.getUnitValue());
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator + (const T &value)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ + value);
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator - (const T &value)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ - value);
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator * (const T &value)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ * value);
    return(rav);
}
template<typename T, size_t dimensions>
Angle<T, dimensions> Angle<T, dimensions>::operator / (const T &value)const{
    Angle<T, dimensions> rav = Angle<T, dimensions>(this->angles_ / value);
    return(rav);
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator += (const Angle<T, dimensions> &p){
    std::cout << "[INFO]: Angle Adding/Setting: " << p << "\n";//!Debugging
    this->angles_ += p.getUnitValue();
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator -= (const Angle<T, dimensions> &p){
    this->angles_ -= p.getUnitValue();
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator *= (const Angle<T, dimensions> &p){
    this->angles_ *= p.getUnitValue();
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator /= (const Angle<T, dimensions> &p){
    this->angles_ /= p.getUnitValue();
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator += (const T &value){
    this->angles_ += value;
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator -= (const T &value){
    this->angles_ -= value;
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator *= (const T &value){
    this->angles_ *= value;
    this->simplify();
}
template<typename T, size_t dimensions>
void Angle<T, dimensions>::operator /= (const T &value){
    this->angles_ /= value;
    this->simplify();
}

#endif // ANGLE_CPP_
