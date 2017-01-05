#ifndef BOX_CPP_
#define BOX_CPP_

#include "Box.hpp"
using namespace scorpion::geometry;

//Variables

//Constructors
template<typename T, size_t dimensions>
Box<T, dimensions>::Box(T* collection1[dimensions], T* collection2[dimensions]) : p1(collection1), p2(collection2){
}
template<typename T, size_t dimensions>
Box<T, dimensions>::Box(Point<T, dimensions> pr1, Point<T, dimensions> pr2) : p1(pr1), p2(pr2){
}
template<typename T, size_t dimensions>
Box<T, dimensions>::Box(std::initializer_list<T> c) : p1(), p2(){
    for(size_t i = 0u; i < dimensions; i++){
        //Define each simultaneously offset by dimensions size
        //Validate Value Ranges
        if(i >= c.size()){
            //A required point is outside of range
            this->p1.setValue(i, (T)0);
        }else{
            //std::cout << "[INFO]: Box Point 1[" << i << "] next value: " << (T)(*(c.begin() + i)) << "\n";//!debugging
            this->p1.setValue(i, (T)(*(c.begin() + i)));
        }
        if((i + dimensions) >= c.size()){
            //A required point is outside of range
            this->p2.setValue((i), (T)0);
        }else{
            //std::cout << "[INFO]: Box Point 2[" << (i) << "] next value: " << (T)(*(c.begin() + dimensions + i)) << "\n";//!debugging
            this->p2.setValue((i), (T)(*(c.begin() + dimensions + i)));
        }
    }
}
template<typename T, size_t dimensions>
Box<T, dimensions>::Box(std::initializer_list<T> c1, std::initializer_list<T> c2) : p1(c1), p2(c2){
    //std::cout << "[INFO]: New Box Points: P1: " << this->p1 << "\tP2: " << this->p2 << "\n";//!Debugging
}
template<typename T, size_t dimensions>
Box<T, dimensions>::~Box(){}

//Functions
template<typename T, size_t dimensions>
bool Box<T, dimensions>::isSquare() const{
    //Note: function is not limited to 2 dimensions
    if(dimensions <= 1u)return(false);
    for(size_t i = 1u; i < dimensions; i++)
        if(this->getDimensionSize(0) != this->getDimensionSize(i))
            return(false);
    return(true);
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::touchs(const Box<T, dimensions> box_) const{
    return(this->touchs(&box_));
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::touchs(const Box<T, dimensions>* box_) const{
    //Validate
    if(box_ == nullptr)return(false);
    //Local Variables
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        if(this->getDimensionLargest(i) < box_->getDimensionSmallest(i) ||
           this->getDimensionSmallest(i) > box_->getDimensionLargest(i))
            return(false);
    //if this upper larger bound is greater than their lower smaller bound of the same dimension maybe then touching
    //or if this lower smaller bound is less than their upper larger bound of the same dimension maybe then touching
    //Finish
    return(true);
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::contains(const Point<T, dimensions> p_) const{
    return(this->contains(&p_));
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::contains(const Point<T, dimensions>* p_) const{
    //Validate
    if(p_ == nullptr)return(false);
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        if(p_->getValue(i) > this->getDimensionLargest(i) ||
           p_->getValue(i) < this->getDimensionSmallest(i))
            return(false);
    //Finish
    return(true);
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::contains(const Box<T, dimensions> box_) const{
    return(this->contains(&box_));
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::contains(const Box<T, dimensions>* box_) const{
    //Validate
    if(box_ == nullptr)return(false);
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        if(box_->getDimensionLargest(i) > this->getDimensionLargest(i) ||
           box_->getDimensionSmallest(i) < this->getDimensionSmallest(i))
            return(false);
    //Finish
    return(true);
}
template<typename T, size_t dimensions>
size_t Box<T, dimensions>::getDimensions() const{
    return(dimensions);
}
template<typename T, size_t dimensions>
T Box<T, dimensions>::getDimensionLargest(const std::string dimensionNames) const{
    return((this->p2.getValue(dimensionNames) > this->p1.getValue(dimensionNames)) ? this->p2.getValue(dimensionNames) : this->p1.getValue(dimensionNames));
}
template<typename T, size_t dimensions>
T Box<T, dimensions>::getDimensionLargest(const size_t dimension_index_) const{
    //std::cout << "[INFO]: Dimension[" << dimension_index_ << "] Largest value1: " << this->p1.getValue(dimension_index_) << "\tvalue2: " << this->p2.getValue(dimension_index_) << "\n";
    return((this->p2.getValue(dimension_index_) > this->p1.getValue(dimension_index_)) ? this->p2.getValue(dimension_index_) : this->p1.getValue(dimension_index_));
}
template<typename T, size_t dimensions>
T Box<T, dimensions>::getDimensionSmallest(const std::string dimensionNames) const{
    return((this->p2.getValue(dimensionNames) < this->p1.getValue(dimensionNames)) ? this->p2.getValue(dimensionNames) : this->p1.getValue(dimensionNames));
}
template<typename T, size_t dimensions>
T Box<T, dimensions>::getDimensionSmallest(const size_t dimension_index_) const{
    //std::cout << "[INFO]: Dimension[" << dimension_index_ << "] Smallest Value1: " << this->p1.getValue(dimension_index_) << "\tValue2: " << this->p2.getValue(dimension_index_) << "\n";
    return((this->p2.getValue(dimension_index_) < this->p1.getValue(dimension_index_)) ? this->p2.getValue(dimension_index_) : this->p1.getValue(dimension_index_));
}
template<typename T, size_t dimensions>
T Box<T, dimensions>::getDimensionSize(const std::string dimensionName) const{
    //Local Variables
    T rtv = (T)0;
    //Process
    rtv = this->p1.getValue(dimensionName) - this->p2.getValue(dimensionName);
    if(rtv < (T)0)rtv *= -1;//abs without the double constraint
    //Finish
    return(rtv);
}
template<typename T, size_t dimensions>
T Box<T, dimensions>::getDimensionSize(const size_t dimension_index) const{
    //Local Variables
    T rtv = (T)0;
    //Process
    rtv = this->p1.getValue(dimension_index) - this->p2.getValue(dimension_index);
    if(rtv < (T)0)rtv *= -1;//abs without the double constraint
    //Finish
    return(rtv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Box<T, dimensions>::getSize() const{
    //Local Variables
    Point<T, dimensions> rpv;
    T nextTV = (T)0;
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        nextTV = (T)(this->getDimensionLargest(i) - this->getDimensionSmallest(i));
        if(nextTV < (T)0)nextTV *= (T)-1;//!Should not be needed
        rpv.setValue(i, nextTV);
    }
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Box<T, dimensions>::getCenter() const{
    //Local Variables
    Point<T, dimensions> rpv;
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, (T)((this->getDimensionLargest(i) - this->getDimensionSmallest(i)) / (T)2.0));
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Box<T, dimensions>::getLargestDimensionPoint() const{
    //Local Variables
    Point<T, dimensions> rpv = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getDimensionLargest(i));
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Box<T, dimensions>::getSmallestDimensionPoint() const{
    //Local Variables
    Point<T, dimensions> rpv = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        //std::cout << "[INFO]: Box current smallest dimension[" << i << "] value: " << this->getDimensionSmallest(i) << "\n";//!Debugging
        rpv.setValue(i, this->getDimensionSmallest(i));
    }
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Box<T, dimensions>::getNext(const Point<T, dimensions> current_, const Point<T, dimensions> changeOf_, const bool makeSafe) const{
    //Validate
    if(changeOf_ == Point<T, dimensions>())return(current_);
    //Local Variables
    Point<T, dimensions> rpv = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        rpv.setValue(i, ((T)current_.getValue(i) + (T)changeOf_.getValue(i)));
        if(rpv.getValue(i) >= this->getDimensionSmallest(i) && rpv.getValue(i) <= this->getDimensionLargest(i))continue;
        if(makeSafe){
            while(rpv.getValue(i) > this->getDimensionLargest(i))
                rpv.setValue(i, (rpv.getValue(i) - this->getDimensionSize(i)));
            while(rpv.getValue(i) < this->getDimensionSmallest(i))
                rpv.setValue(i, (rpv.getValue(i) + this->getDimensionSize(i)));
        }else{
            rpv.setValue(i, ((rpv.getValue(i) > this->getDimensionLargest(i)) ?
                             (this->getDimensionLargest(i)) : (this->getDimensionSmallest(i))));
        }
    }
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Box<T, dimensions> Box<T, dimensions>::getOverlap(Box<T, dimensions> box_) const{
    return(this->getOverlap(&box_));
}
template<typename T, size_t dimensions>
Box<T, dimensions> Box<T, dimensions>::getOverlap(Box<T, dimensions>* box_) const{
    //Validate
    if(box_ == nullptr)return(Box<T, dimensions>());
    if(!this->touchs(box_))return(Box<T, dimensions>());
    //Local Variables
    Point<T, dimensions> p1 = Point<T, dimensions>(), p2 = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        //Smallest of the largest
        p1.setValue(i, ((this->getDimensionLargest(i) > box_->getDimensionLargest(i)) ? box_->getDimensionLargest(i) : this->getDimensionLargest(i)));
        //Largest of the smallest
        p2.setValue(i, ((this->getDimensionSmallest(i) < box_->getDimensionSmallest(i)) ? box_->getDimensionSmallest(i) : this->getDimensionSmallest(i)));
    }
    //Finish
    return(Box<T, dimensions>(p1, p2));
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::setDimensionSmallest(const size_t dimension_index, const T value){
    //Validate
    if(dimension_index > dimensions)return;//!>=?
    //Local Variables
    //Process
    if(this->p1.getValue(dimension_index) <= this->p2.getValue(dimension_index)){
        //p1 is the Smallest!
        this->p1.setValue(dimension_index, value);
    }else{
        //p2 is the Smallest
        this->p2.setValue(dimension_index, value);
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::setDimensionSmallest(const std::string dimensionName, const T value){
    //Validate
    if(dimensionName.empty())return;
    //Local Variables
    //Process
    if(this->p1.getValue(dimensionName) <= this->p2.getValue(dimensionName)){
        //p1 is the Smallest!
        this->p1.setValue(dimensionName, value);
    }else{
        //p2 is the Smallest
        this->p2.setValue(dimensionName, value);
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::setDimensionLargest(const size_t dimension_index, const T value){
    //Validate
    if(dimension_index > dimensions)return;//!>=?
    //Local Variables
    //Process
    if(this->p1.getValue(dimension_index) >= this->p2.getValue(dimension_index)){
        //p1 is the Largest
        this->p1.setValue(dimension_index, value);
    }else{
        //p2 is the Largest
        this->p2.setValue(dimension_index, value);
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::setDimensionLargest(const std::string dimensionName, const T value){
    //Validate
    if(dimensionName.empty())return;
    //Local Variables
    //Process
    if(this->p1.getValue(dimensionName) >= this->p2.getValue(dimensionName)){
        //p1 is the Largest
        this->p1.setValue(dimensionName, value);
    }else{
        //p2 is the Largest
        this->p2.setValue(dimensionName, value);
    }
}

//Methods
template<typename T, size_t dimensions>
void Box<T, dimensions>::shift(Point<T, dimensions> p_){
    this->shift(&p_);
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::shift(Point<T, dimensions>* p_){
    //Validate
    if(p_ == nullptr)return;
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        this->p1.setValue(i, (this->p1.getValue(i) + p_->getValue(i)));
        this->p2.setValue(i, (this->p2.getValue(i) + p_->getValue(i)));
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::scale(Point<T, dimensions> p_){
    this->scale(&p_);
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::scale(Point<T, dimensions>* p_){
    //!TODO
    //Validate
    if(p_ == nullptr)return;
    //Local Variable
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        //!;
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::debug(std::ostream* os_) const{//!Temporary(?)
    if(os_ == nullptr)os_ = (std::ostream*)&std::cout;
    (*os_) << "[INFO]: Debugging Box Class @ " << (this) << "\n";//!Debugging
    (*os_) << "[INFO]: Debugging Box Points(" << 2u << ")[" << 0u << "]:\n";//!Debugging
    this->p1.debug(os_);//!Debugging
    (*os_) << "[INFO]: Debugging Box Points(" << 2u << ")[" << 1u << "]:\n";//!Debugging
    this->p2.debug(os_);//!Debugging
    (*os_) << "[INFO]: Finished Debugging Box Points...\n";//!Debugging
    (*os_) << "[INFO]: Finished Debugging Box Class @ " << (this) << "\n";//!Debugging
}

//Operators
template<typename T, size_t dimensions>
bool Box<T, dimensions>::operator != (const Box<T, dimensions> &p) const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->getDimensionLargest(i) != p.getDimensionLargest(i) ||
           this->getDimensionSmallest(i) != p.getDimensionSmallest(i))return(true);
    return(false);
}
template<typename T, size_t dimensions>
bool Box<T, dimensions>::operator == (const Box<T, dimensions> &p) const{
    for(size_t i = 0u; i < dimensions; i++)
        if(this->getDimensionLargest(i) != p.getDimensionLargest(i) ||
           this->getDimensionSmallest(i) != p.getDimensionSmallest(i))return(false);
    return(true);
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::operator += (const Box<T, dimensions> &p){
    for(size_t i = 0u; i < dimensions; i++){
        this->p1.setValue(i, this->p1.getValue(i) + p.p1.getValue(i));
        this->p2.setValue(i, this->p2.getValue(i) + p.p2.getValue(i));
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::operator += (const T &value){
    for(size_t i = 0u; i < dimensions; i++){
        this->p1.setValue(i, this->p1.getValue(i) + value);
        this->p2.setValue(i, this->p2.getValue(i) + value);
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::operator -= (const Box<T, dimensions> &p){
    for(size_t i = 0u; i < dimensions; i++){
        this->p1.setValue(i, this->p1.getValue(i) - p.p1.getValue(i));
        this->p2.setValue(i, this->p2.getValue(i) - p.p2.getValue(i));
    }
}
template<typename T, size_t dimensions>
void Box<T, dimensions>::operator -= (const T &value){
    for(size_t i = 0u; i < dimensions; i++){
        this->p1.setValue(i, this->p1.getValue(i) - value);
        this->p2.setValue(i, this->p2.getValue(i) - value);
    }
}

#endif // BOX_CPP_
