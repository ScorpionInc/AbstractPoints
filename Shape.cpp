#include "Shape.hpp"
using namespace scorpion::geometry;

#ifndef SHAPE_CPP_
#define SHAPE_CPP_

//Variables

//Constructors
template<typename T, size_t dimensions>
Shape<T, dimensions>::Shape() : points_(){
}
template<typename T, size_t dimensions>
Shape<T, dimensions>::Shape(const std::vector<Point<T, dimensions> > &buffer_) : points_(){
    for(size_t i = 0u; i < buffer_.size(); i++){
        this->addPoint(buffer_[i]);
    }
}
template<typename T, size_t dimensions>
Shape<T, dimensions>::~Shape(){}

//Functions
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::isConcave() const{
    //!TODO
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::isConvex() const{
    return(!this->isConcave());
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::hasOverlaps() const{
    //!TODO
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::isValid() const{
    //!TODO
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::contains(const Point<T, dimensions> &point_) const{
    //!TODO Add check for max value
    Angle<T, dimensions> theta_ = Angle<T, dimensions>();
    Angle<T, dimensions> delta_ = Angle<T, dimensions>();
    Angle<T, dimensions> i_angle_ = Angle<T, dimensions>();
    Angle<T, dimensions> n_angle_ = Angle<T, dimensions>();
    size_t next_index_ = (size_t)0;
    for(size_t i = 0u; i < this->points_.size(); i++){
        next_index_ = ((i + 1 < this->points_.size()) ? i + 1u : 0u);
        i_angle_.setTo(point_, this->points_[i]);
        std::cout << "[INFO]: Angle to point[" << i << "]: " << i_angle_ << "\n";//!Debugging
        n_angle_.setTo(point_, this->points_[next_index_]);
        std::cout << "[INFO]: Angle to next point: " << n_angle_ << "\n";//!Debugging
        //delta_ = (i_angle_ - n_angle_);
        delta_ = i_angle_;
        //std::cout << "[INFO]: Set Test: " << delta_ << "\n";//!Debugging
        delta_ += n_angle_;delta_.setDirection(false);
        std::cout << "[INFO]: Angle Diff. to next point: " << delta_ << "\n";//!Debugging
        theta_ += delta_;
        std::cout << "[INFO]: Theta Angle is Currently: " << theta_ << "\n";//!Debugging
    }
    return(theta_ == Angle<T, dimensions>() || theta_ == Angle<T, dimensions>());
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::contains(const Shape<T, dimensions> &shape_) const{
    for(size_t i = 0u; i < shape_.pointCount(); i++)
        if(!this->contains(shape_.getPoint(i)))return(false);
    return(shape_.isValid() && shape_.pointCount() > 0u);
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::touchs(const Shape<T, dimensions> &shape_) const{
    //!Remember to test both sets of points
    if(this->pointCount() <= 0u || shape_.pointCount() <= 0u)return(false);
    for(size_t i = 0u; i < this->points_.size(); i++)
        if(shape_.contains(this->points_[i]))return(true);
    for(size_t i = 0u; i < shape_.pointCount(); i++)
        if(this->contains(shape_.getPoint(i)))return(true);
    return(false);
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::hasPoint(const Point<T, dimensions> &point_) const{
    for(size_t i = 0u; i < this->points_.size(); i++)
        if(this->points_[i] == point_)return(true);
    return(false);
}
template<typename T, size_t dimensions>
bool Shape<T, dimensions>::hasPoint(const std::initializer_list<T> c_) const{
    return(this->hasPoint(Point<T, dimensions>(c_)));
}
template<typename T, size_t dimensions>
size_t Shape<T, dimensions>::pointCount() const{
    return(this->points_.size());
}
template<typename T, size_t dimensions>
T Shape<T, dimensions>::getDimensionLargest(const std::string name_) const{
    T currentLargest_ = static_cast<T>(0);
    if(this->points_.size() <= 0u || name_.empty())return(currentLargest_);
    for(size_t i = 0u; i < this->points_.size(); i++)
        if(this->points_[i].getValue(name_) > currentLargest_)currentLargest_ = this->points_[i].getValue(name_);
    return(currentLargest_);
}
template<typename T, size_t dimensions>
T Shape<T, dimensions>::getDimensionLargest(const size_t index_) const{
    T currentLargest_ = static_cast<T>(0);
    if(this->points_.size() <= 0u || index_ >= dimensions)return(currentLargest_);
    for(size_t i = 0u; i < this->points_.size(); i++)
        if(this->points_[i].getValue(index_) > currentLargest_)currentLargest_ = this->points_[i].getValue(index_);
    return(currentLargest_);
}
template<typename T, size_t dimensions>
T Shape<T, dimensions>::getDimensionSmallest(const std::string name_) const{
    T currentSmallest = static_cast<T>(0);
    if(this->points_.size() <= 0u || name_.empty())return(currentSmallest);
    currentSmallest = this->points_[0u].getValue(name_);
    for(size_t i = 0u; i < this->points_.size(); i++)
        if(this->points_[i].getValue(name_) < currentSmallest)currentSmallest = this->points_[i].getValue(name_);
    return(currentSmallest);
}
template<typename T, size_t dimensions>
T Shape<T, dimensions>::getDimensionSmallest(const size_t index_) const{
    T currentSmallest = static_cast<T>(0);
    if(this->points_.size() <= 0u || index_ >= dimensions)return(currentSmallest);
    currentSmallest = this->points_[0u].getValue(index_);
    for(size_t i = 0u; i < this->points_.size(); i++)
        if(this->points_[i].getValue(index_) < currentSmallest)currentSmallest = this->points_[i].getValue(index_);
    return(currentSmallest);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Shape<T, dimensions>::getMaximumPoint() const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getDimensionLargest(i));
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Shape<T, dimensions>::getMinimumPoint() const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getDimensionSmallest(i));
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Shape<T, dimensions>::getCenterOfMass() const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    if(this->points_.size() <= 0u)return(rpv);
    for(size_t i = 0u; i < this->points_.size(); i++)
        rpv += this->points_[i];
    return(rpv / static_cast<T>(this->points_.size()));
}
template<typename T, size_t dimensions>
Point<T, dimensions> Shape<T, dimensions>::getPoint(const size_t index_) const{
    return(this->points_[index_]);
}

//Methods
template<typename T, size_t dimensions>
void Shape<T, dimensions>::getPoints(std::vector<Point<T, dimensions> > &buffer_) const{
    buffer_.clear();
    for(size_t i = 0u; i < this->points_.size(); i++){
        buffer_.push_back(this->points_[i]);
    }
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::getNearestPoints(std::vector<size_t> &index_buffer_, const Point<T, dimensions> &target_, bool cull) const{
    //!TODO
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::getNearPoints(std::vector<size_t> &index_buffer_, const Point<T, dimensions> &target_, size_t maximum_, size_t minimum_) const{
    //!TODO
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::getPointsWithin(std::vector<size_t> &index_buffer_, const Point<T, dimensions> &target_, T distance_) const{
    //!TODO
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::addPoint(const Point<T, dimensions> &point_){
    this->points_.push_back(point_);
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::addPoint(const std::initializer_list<T> c_){
    this->addPoint(Point<T, dimensions>(c_));
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::removePoint(const size_t index_){
    if(index_ >= this->points_.size())return;
    this->points_.erase(this->points_.begin() + index_);
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::removePoint(const Point<T, dimensions> &point_){
    for(size_t i = 0u; i < this->points_.size(); i++){
        if(this->points_[i] == point_){
            this->removePoint(i);
            return;
        }
    }
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::removePoint(const std::initializer_list<T> c_){
    this->removePoint(Point<T, dimensions>(c_));
}
template<typename T, size_t dimensions>
void Shape<T, dimensions>::reorderPoints(){
    //!TODO
}//!Self Heal
template<typename T, size_t dimensions>
void Shape<T, dimensions>::clearPoints(){
    this->points_.clear();
}

//Operators

#endif // SHAPE_CPP_
