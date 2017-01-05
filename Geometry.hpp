#include "DimensionPoint.cpp"
#include "Point.cpp"
#include "Angle.cpp"
#include "Shape.cpp"
#include "Box.cpp"
#include "Grid.cpp"
#include "SpatialTree.cpp"
using namespace scorpion::geometry;

#include "AStarFinder.cpp"
#include "CollisionTree.cpp"
using namespace scorpion;

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

template class scorpion::geometry::DimensionPoint<float>;
template class scorpion::geometry::DimensionPoint<double>;
template class scorpion::geometry::DimensionPoint<int>;
template class scorpion::geometry::DimensionPoint<size_t>;

template class scorpion::geometry::Point<float, 2u>;
template class scorpion::geometry::Point<double, 2u>;
template class scorpion::geometry::Point<int, 2u>;
template class scorpion::geometry::Point<size_t, 2u>;

template class scorpion::geometry::Point<float, 3u>;
template class scorpion::geometry::Point<double, 3u>;
template class scorpion::geometry::Point<int, 3u>;
template class scorpion::geometry::Point<size_t, 3u>;

template class scorpion::geometry::Angle<float, 2u>;
template class scorpion::geometry::Angle<float, 3u>;

template class scorpion::geometry::Shape<float, 2u>;
template class scorpion::geometry::Shape<float, 3u>;

template class scorpion::geometry::Box<float, 2u>;
template class scorpion::geometry::Box<double, 2u>;
template class scorpion::geometry::Box<int, 2u>;
template class scorpion::geometry::Box<size_t, 2u>;

template class scorpion::geometry::Box<float, 3u>;
template class scorpion::geometry::Box<double, 3u>;
template class scorpion::geometry::Box<int, 3u>;
template class scorpion::geometry::Box<size_t, 3u>;

template class scorpion::geometry::Grid<float, 3u>;
template class scorpion::geometry::Grid<double, 3u>;
template class scorpion::geometry::Grid<int, 3u>;

template class scorpion::geometry::Grid<float, 2u>;
template class scorpion::geometry::Grid<double, 2u>;
template class scorpion::geometry::Grid<int, 2u>;

template class scorpion::geometry::SpatialTree<float, 2u>;
template class scorpion::geometry::SpatialTree<float, 3u>;

template class scorpion::CollisionTree<float, 2u>;
template class scorpion::CollisionTree<double, 2u>;
template class scorpion::CollisionTree<int, 2u>;

template class scorpion::CollisionTree<float, 3u>;
template class scorpion::CollisionTree<double, 3u>;
template class scorpion::CollisionTree<int, 3u>;

//typedef scorpion::CollisionTree<float, 2u> Quadtree;//!TODO
//typedef scorpion::CollisionTree<float, 3u> Octtree;//!TODO
template<typename T>
using Quadtree = scorpion::CollisionTree<T, 2u>;

template class scorpion::AStarFinder<float>;
template class scorpion::AStarFinder<double>;
template class scorpion::AStarFinder<int>;

#endif // GEOMETRY_HPP_
