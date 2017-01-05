#include "Grid.hpp"
using namespace scorpion::geometry;

#ifndef GRID_CPP_
#define GRID_CPP_

//Variables

//Constructors
template<typename T, size_t dimensions>
Grid<T, dimensions>::Grid(Box<T, dimensions> bounds_, Point<size_t, dimensions> nodeCount_) : bounds(), nodeCount(nodeCount_){
    this->init(bounds_, nodeCount_);
}
template<typename T, size_t dimensions>
Grid<T, dimensions>::Grid(Point<T, dimensions> nodeSize_, Point<size_t, dimensions> nodeCount_) : bounds(), nodeCount(nodeCount_){
    this->init(nodeSize_, nodeCount_);
}
template<typename T, size_t dimensions>
Grid<T, dimensions>::~Grid(){}

//Functions
template<typename T, size_t dimensions>
bool Grid<T, dimensions>::inRange(const Point<T, dimensions> point_) const{
    return(this->bounds.contains(point_));
}
template<typename T, size_t dimensions>
bool Grid<T, dimensions>::hasIndex(const Point<size_t, dimensions> index_) const{
    //return(index_ <= this->nodeCount);
    return(index_ < this->nodeCount);
}
template<typename T, size_t dimensions>
Box<T, dimensions> Grid<T, dimensions>::getBounds() const{
    return(this->bounds);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Grid<T, dimensions>::getNodeSize() const{
    //Local Variables
    Point<T, dimensions> rpv = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, (this->bounds.getDimensionSize(i)) / this->nodeCount.getValue(i));
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<size_t, dimensions> Grid<T, dimensions>::getCounts() const{
    return(this->nodeCount);
}
template<typename T, size_t dimensions>
size_t Grid<T, dimensions>::getCount(const size_t dimension_index) const{
    if(dimension_index > dimensions)return(0u);//!>=?
    return(this->nodeCount.getValue(dimension_index));
}
template<typename T, size_t dimensions>
size_t Grid<T, dimensions>::getCount(const std::string dimension_name) const{
    if(dimension_name.empty())return(0u);
    return(this->nodeCount.getValue(dimension_name));
}
template<typename T, size_t dimensions>
Point<size_t, dimensions> Grid<T, dimensions>::getIndex(const Point<T, dimensions> point_) const{
    //Local Variables
    Point<size_t, dimensions> rpv = Point<size_t, dimensions>();
    Point<T, dimensions> nodeS = this->getNodeSize();
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, (size_t)( floorl((long double)point_.getValue(i) / (long double)nodeS.getValue(i))) );
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Grid<T, dimensions>::getPoint(const Point<size_t, dimensions> index_) const{
    //Local Variables
    Point<T, dimensions> rpv = Point<T, dimensions>();
    Point<T, dimensions> nodeS = this->getNodeSize();
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, (nodeS.getValue(i) * index_.getValue(i)));
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<size_t, dimensions> Grid<T, dimensions>::getNextIndex(const Point<size_t, dimensions> current_, const Point<size_t, dimensions> changeOf_, const bool makeSafe) const{
    //Validate
    for(size_t i = 0u; i < dimensions; i++)
        if(this->nodeCount.getValue(i) == 0u)return(current_);
    if(changeOf_ == Point<size_t, dimensions>())return(current_);
    //Local Variables
    Point<size_t, dimensions> rpv = Point<size_t, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        rpv.setValue(i, current_.getValue(i) + changeOf_.getValue(i));
        if(rpv.getValue(i) < this->nodeCount.getValue(i) && rpv.getValue(i) >= (size_t)0u)continue;
        if(makeSafe){
            if(this->nodeCount.getValue(i) != 0u)
            while(rpv.getValue(i) >= this->nodeCount.getValue(i))
                rpv.setValue(i, (rpv.getValue(i) - this->nodeCount.getValue(i)));
        }else{
            rpv.setValue(i, ((rpv.getValue(i) >= this->nodeCount.getValue(i)) ?
                            ((this->nodeCount.getValue(i) <= (size_t)0u) ?
                             (size_t)0u : this->nodeCount.getValue(i) - 1u) : ((size_t)0u)));
        }
    }
    //Finish
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Grid<T, dimensions>::getNextPoint(const Point<T, dimensions> current_, const Point<T, dimensions> changeOf_, const bool makeSafe) const{
    //Finish
    return(this->bounds.getNext(current_, changeOf_, makeSafe));
}

//Methods
template<typename T, size_t dimensions>
void Grid<T, dimensions>::init(const Box<T, dimensions> bounds_, const Point<size_t, dimensions> nodeCount_){
    this->bounds = bounds_;
    this->nodeCount = nodeCount_;
}
template<typename T, size_t dimensions>
void Grid<T, dimensions>::init(const Point<T, dimensions> nodeSize_, const Point<size_t, dimensions> nodeCount_){
    for(size_t i = 0u; i < dimensions; i++)
        this->bounds.setDimensionLargest(i, nodeSize_.getValue(i) * nodeCount_.getValue(i));
    this->nodeCount = nodeCount_;
}
template<typename T, size_t dimensions>
void Grid<T, dimensions>::resizeTo(const Box<T, dimensions> bounds_){
    this->bounds = bounds_;
}
template<typename T, size_t dimensions>
void Grid<T, dimensions>::setPartsTo(const Point<size_t, dimensions> nodeCount_){
    this->nodeCount = nodeCount_;
}
template<typename T, size_t dimensions>
void Grid<T, dimensions>::setNodeSize(const Point<T, dimensions> nodeSize){
    for(size_t i = 0u; i < dimensions; i++){
        this->bounds.setDimensionSmallest(i, (T)0);
        this->bounds.setDimensionLargest(i, nodeSize.getValue(i) * this->nodeCount.getValue(i));
    }
}
template<typename T, size_t dimensions>
void Grid<T, dimensions>::debug(std::ostream* os_) const{//!Temporary(?)
    //Validate
    if(os_ == nullptr)os_ = (std::ostream*)&std::cout;
    //Process
    (*os_) << "[INFO]: Starting Debug of Grid @ " << (this) << "\n";//!Debugging
    (*os_) << "[INFO]: Grid Bounds: " << this->bounds << "\n";
    (*os_) << "[INFO]: Node Size: " << this->getNodeSize() << "\n";
    (*os_) << "[INFO]: Node Counts: " << this->nodeCount << "\n";
    (*os_) << "[INFO]: Stopping Debug of Grid @ " << (this) << "\n";//!Debugging
}

//Operators

#endif // GRID_CPP_
