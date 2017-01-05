/* Notes:
 * Version: 1.0.0.0
 * Author: ScorpionInc
 * Purpose: Superclass for my implementations of multidimensional spatial trees
 * Created: 20151227
 * Last Updated: 20151227
 * TODO:
 * 1) Make a TODO list...
//*/
#include <iostream>//!For Debugging
#include <vector>
#include <string>

#include "Shape.cpp"

#ifndef SPATIALTREE_HPP_
#define SPATIALTREE_HPP_

namespace scorpion{
namespace geometry{
    template<typename T, size_t dimensions>
    class SpatialTree{
    public:
        struct SpatialTreeItem{
            Shape<T, dimensions> bounds;
            void* child_ = nullptr;
        };
        SpatialTree();
        virtual ~SpatialTree();
        static std::string getTreeName();
        void add(Shape<T, dimensions> bounds, void* child_);
        virtual void add(SpatialTreeItem child_);
        virtual void query(std::vector<SpatialTreeItem> &buffer_, Shape<T, dimensions> q_bounds_, std::vector<void*> &skips_ = std::vector<void*>()) const;
        virtual void clear();
    protected:
        static std::string treeName_;
        std::vector<SpatialTreeItem> children_;
        std::vector<SpatialTree<T, dimensions>* > branches_;
    private:
    };
}
}

#endif // SPATIALTREE_HPP_
