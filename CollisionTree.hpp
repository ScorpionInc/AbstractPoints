#include <iostream>
#include <vector>

#include "Box.cpp"
using namespace scorpion::geometry;

#ifndef COLLISIONTREE_HPP_
#define COLLISIONTREE_HPP_

//typedef CollisionTree<typename T, 2u> QuadTree;
//typedef CollisionTree<typename T, 3u> OctTree;
namespace scorpion{
    template<typename T, size_t dimensions>
    class CollisionTree{
        public:
            struct CollisionTreeItem{
                Box<T, dimensions> bounds;
                void* child = nullptr;
            };
            size_t Max_Children, Min_Children, Max_Layers;
            size_t layer_;
            Box<T, dimensions> bounds_;
            CollisionTree(Box<T, dimensions> bounds = Box<T, dimensions>());
            ~CollisionTree();
            bool hasChildren();
            bool isLeaf();
            bool hasSubtrees();
            bool hasChild(CollisionTreeItem item, bool nodeTest = false);
            bool hasChild(Box<T, dimensions> bounds, void* child, bool nodeTest = false);
            bool hasChild(Box<T, dimensions>* bounds, void* child, bool nodeTest = false);
            size_t childCount(bool nodeTest = false);
            size_t nodeCount(bool nodeTest = false);
            void split();//Subdivides bounds
            void autoMerge();//!TODO//Tests minimum children in nodes then merges
            void merge(size_t node_index);//Transfers all children from specific node into parent Node(up)
            void merge();//Transfers all children from nodes_ into parent node(up)
            void join();//Transfers all children to child node(s)(down)
            void addChild(CollisionTreeItem item_);
            void addChild(Box<T, dimensions> bounds, void* child_ = nullptr);
            void addChild(Box<T, dimensions>* bounds, void* child_ = nullptr);
            void query(Box<T, dimensions> bounds, std::vector<CollisionTreeItem>* buffer);
            void query(Box<T, dimensions> bounds, std::vector<Box<T, dimensions> >* b_buffer, std::vector<void*>* c_buffer);
            void query(Box<T, dimensions> bounds, std::vector<Box<T, dimensions> >* buffer);
            void query(Box<T, dimensions> bounds, std::vector<void*>* buffer);
            void query(Box<T, dimensions>* bounds, std::vector<CollisionTreeItem>* buffer);
            void query(Box<T, dimensions>* bounds, std::vector<Box<T, dimensions> >* b_buffer, std::vector<void*>* c_buffer);
            void query(Box<T, dimensions>* bounds, std::vector<Box<T, dimensions> >* buffer);
            void query(Box<T, dimensions>* bounds, std::vector<void*>* buffer);
            void debug(std::ostream* os_ = nullptr);//!Temporary(?)
            //Operator(s)
            friend std::ostream& operator <<(std::ostream& os, const CollisionTree<T, dimensions>& tree_){
                //!TODO
                return(os);
            }
        protected:
            std::vector<CollisionTree<T, dimensions>* > nodes_;
            std::vector<CollisionTreeItem> children_;
        private:
            static void subdivide(Box<T, dimensions> bounds, size_t parts, std::vector<Box<T, dimensions> >* buffer);
            static void subdivide(Box<T, dimensions>* bounds, size_t parts, std::vector<Box<T, dimensions> >* buffer);
            static void subdivide(Box<T, dimensions> bounds, size_t parts, std::vector<Box<T, dimensions>* >* buffer);
            static void subdivide(Box<T, dimensions>* bounds, size_t parts, std::vector<Box<T, dimensions>* >* buffer);
    };
}

#endif // COLLISIONTREE_HPP_
