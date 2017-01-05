#include "DimensionGrid.hpp"
using namespace scorpion;

#ifndef DIMENSIONGRID_CPP_
#define DIMENSIONGRID_CPP_

//Variables

//Constructors
template<typename T, typename S, size_t dimensions>
DimensionGrid<T, S, dimensions>::DimensionGrid(Point<S, dimensions> size__, S nodeSize) : size_(size__), data_(nullptr){
    this->init(this->size_, nodeSize);
}
template<typename T, typename S, size_t dimensions>
DimensionGrid<T, S, dimensions>::~DimensionGrid(){}

//Functions
template<typename T, typename S, size_t dimensions>
size_t DimensionGrid<T, S, dimensions>::getNodeCount(const size_t dimension_index) const{
    //!TODO
    //Validate
    if(dimension_index >= dimensions)return((size_t)0u);
    //Local Variables
    //Process
}
template<typename T, typename S, size_t dimensions>
Point<size_t, dimensions> DimensionGrid<T, S, dimensions>::getNodeSizes() const{//getCount
    //!TODO
    //Validate
    if(this->data_ == nullptr)return(Point<size_t, dimensions>());
    //Local Variables
    Point<size_t, dimensions> rpv = Point<size_t, dimensions>();
    //Process
    //Finish
    return(rpv);
}
template<typename T, typename S, size_t dimensions>
Point<S, dimensions> DimensionGrid<T, S, dimensions>::getDimensionSizes() const{//getWidth
    return(this->size_);
}

//Methods
template<typename T, typename S, size_t dimensions>
void DimensionGrid<T, S, dimensions>::init(const Point<S, dimensions> size_, const S nodeSize){
    //!TODO
    //Validate
    if(nodeSize == (S)0)return;//!?
    //Local Variables
    size_t parts = 0u;
    S currentDimension = (S)0;
    void* lastVector = nullptr;
    //Process
    if(this->data_ == nullptr)this->data_ = new std::vector<void*>();
    for(size_t i = 0u; i < dimensions; i++){
        parts = 0u;
        currentDimension = size_.getValue(i);
        lastVector = this->data_;
        while(currentDimension > nodeSize){
            currentDimension -= nodeSize;
            parts += 1u;
        }
        for(size_t ii = 0u; ii < i; ii++)
            lastVector = (*(std::vector<void*>*)lastVector).back();
    }
}
template<typename T, typename S, size_t dimensions>
void DimensionGrid<T, S, dimensions>::debug(std::ostream* os_)const{//!Temporary(?)
    //Validate
    if(os_ == nullptr)os_ = (std::ostream*)(&std::cout);
    //Process
    //!TODO
}

//Operators

#endif // DIMENSIONGRID_CPP_
