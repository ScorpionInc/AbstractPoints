#include "SpatialTree.hpp"
using namespace scorpion::geometry;

#ifndef SPATIALTREE_CPP_
#define SPATIALTREE_CPP_

//Variables
template<typename T, size_t dimensions>
std::string SpatialTree<T, dimensions>::treeName_ = std::string("Generic");

//Constructors
template<typename T, size_t dimensions>
SpatialTree<T, dimensions>::SpatialTree() : children_(), branches_(){
}
template<typename T, size_t dimensions>
SpatialTree<T, dimensions>::~SpatialTree(){}

//Functions
template<typename T, size_t dimensions>
std::string SpatialTree<T, dimensions>::getTreeName(){
    return(SpatialTree<T, dimensions>::treeName_);
}

//Methods
template<typename T, size_t dimensions>
void SpatialTree<T, dimensions>::add(Shape<T, dimensions> bounds, void* child_){
    SpatialTreeItem item_;
    item_.bounds = bounds;item_.child_ = child_;
    this->add(item_);
}
template<typename T, size_t dimensions>
void SpatialTree<T, dimensions>::add(SpatialTreeItem child_){
    //!*Virtual*
}
template<typename T, size_t dimensions>
void SpatialTree<T, dimensions>::query(std::vector<SpatialTreeItem> &buffer_, Shape<T, dimensions> q_bounds_, std::vector<void*> &skips_) const{
    //!*Virtual*
}
template<typename T, size_t dimensions>
void SpatialTree<T, dimensions>::clear(){
    //!*Virtual*
    this->children_.clear();
    this->branches_.clear();
}

#endif // SPATIALTREE_CPP_
