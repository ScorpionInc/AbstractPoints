#include "CollisionTree.hpp"
using namespace scorpion;

#ifndef COLLISIONTREE_CPP_
#define COLLISIONTREE_CPP_

//Variables

//Constructors
template<typename T, size_t dimensions>
CollisionTree<T, dimensions>::CollisionTree(Box<T, dimensions> bounds) :
    Max_Children(20u), Min_Children(2u), Max_Layers(10u), layer_(0u),
    bounds_(bounds), nodes_(), children_(){
}
template<typename T, size_t dimensions>
CollisionTree<T, dimensions>::~CollisionTree(){}

//Functions
template<typename T, size_t dimensions>
bool CollisionTree<T, dimensions>::hasChildren(){
    return(this->children_.size() > 0u);
}
template<typename T, size_t dimensions>
bool CollisionTree<T, dimensions>::isLeaf(){
    return(this->nodes_.size() <= 0u);
}
template<typename T, size_t dimensions>
bool CollisionTree<T, dimensions>::hasSubtrees(){
    return(this->nodes_.size() > 0u);
}
template<typename T, size_t dimensions>
bool CollisionTree<T, dimensions>::hasChild(CollisionTreeItem item, bool nodeTest){
    return(this->hasChild(&item.bounds, item.child));
}
template<typename T, size_t dimensions>
bool CollisionTree<T, dimensions>::hasChild(Box<T, dimensions> bounds, void* child, bool nodeTest){
    return(this->hasChild(&bounds, child));
}
template<typename T, size_t dimensions>
bool CollisionTree<T, dimensions>::hasChild(Box<T, dimensions>* bounds, void* child, bool nodeTest){
    //Validate
    if(bounds == nullptr)return(false);
    //Local Variables
    //Process
    for(size_t i = 0u; i < this->children_.size(); i++)
        if(this->children_[i].bounds == (*bounds) &&
           this->children_[i].child == child)
        return(true);
    if(nodeTest)
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        if(this->nodes_[i] == nullptr){
            //!Handle Error
            std::cerr << "[ERROR]: hasChild has Bad Tree Node!\n";
            continue;
        }
        if(this->nodes_[i]->hasChild(bounds, child, nodeTest))return(true);
    }
    return(false);
}
template<typename T, size_t dimensions>
size_t CollisionTree<T, dimensions>::childCount(bool nodeTest){
    //Local Variables
    size_t rsv = 0u;
    //Process
    rsv += this->children_.size();
    if(nodeTest)
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        if(this->nodes_[i] == nullptr){
            //!Handle Error
            std::cerr << "[ERROR]: childCount detected a bad TreeNode!\n";
            continue;
        }
        rsv += this->nodes_[i]->childCount(nodeTest);
    }
    //Finish
    return(rsv);
}
template<typename T, size_t dimensions>
size_t CollisionTree<T, dimensions>::nodeCount(bool nodeTest){
    //Local Variables
    size_t rsv = 0u;
    //Process
    //rsv += this->nodes_.size();//!Faster
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        if(this->nodes_[i] == nullptr)continue;
        rsv += 1u;
        if(nodeTest)rsv += this->nodes_[i]->nodeCount(nodeTest);
    }
    //Finish
    return(rsv);
}

//Methods
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::split(){
    //Subdivides bounds
    //Validate
    if(this->hasSubtrees())return;
    //Local Variables
    std::vector<Box<T, dimensions> > buffer = std::vector<Box<T, dimensions> >();
    //Process
    CollisionTree<T, dimensions>::subdivide(this->bounds_, 2u, &buffer);
    for(size_t i = 0u; i < buffer.size(); i++){
        CollisionTree<T, dimensions>* nextTree = new CollisionTree<T, dimensions>(buffer[i]);
        nextTree->layer_ = (this->layer_ + 1u);
        nextTree->Max_Children = this->Max_Children;
        nextTree->Max_Layers = this->Max_Layers;
        nextTree->Min_Children = this->Min_Children;
        this->nodes_.push_back(nextTree);
    }
    this->join();
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::autoMerge(){
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        if(this->nodes_[i] == nullptr)continue;
        this->nodes_[i]->autoMerge();
        if(this->nodes_[i]->childCount(false) < this->nodes_[i]->Min_Children)
            this->nodes_[i]->merge(i);
    }
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::merge(size_t node_index){
    //Validate
    if(!this->hasSubtrees())return;
    if(node_index >= this->nodes_.size())return;
    if(this->nodes_[node_index] == nullptr)return;
    //Local Variables
    //Process
    this->nodes_[node_index]->merge();
    this->children_.insert(this->children_.begin(),
            this->nodes_[node_index]->children_.begin(),
            this->nodes_[node_index]->children_.end());
    //Finish
    this->nodes_.erase(this->nodes_.begin() + node_index);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::merge(){
    //Transfers all children to parent node(up)
    //Validate
    if(!this->hasSubtrees())return;
    //Local Variables
    //Process
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        if(this->nodes_[i] == nullptr)continue;
        this->nodes_[i]->merge();
        this->children_.insert(this->children_.begin(),
                                this->nodes_[i]->children_.begin(),
                                this->nodes_[i]->children_.end());
    }
    this->nodes_.clear();
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::join(){
    //Transfers all children to child node(s)(down)
    //Validate
    if(!this->hasSubtrees())return;
    //Local Variables
    //Process
    for(size_t i = 0u; i < this->children_.size(); i++)
        this->addChild(this->children_[i]);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::addChild(CollisionTreeItem item_){
    //Validate
    if(!this->bounds_.touchs(item_.bounds)){
        //!Handle Error
        std::cerr << "[ERROR]: AddChild child is outside node Bounds!\n";
        return;
    }
    //Local Variables
    //Process
    if(this->hasSubtrees()){
        //Has Subtrees add child to respective tree(s)
        for(size_t i = 0u; i < this->nodes_.size(); i++){
            if(this->nodes_[i] == nullptr){
                //!Handle Error
                std::cerr << "[ERROR]: AddChild has detected a bad node[" << i << "]!\n";//!Debugging
                continue;
            }
            if(this->nodes_[i]->bounds_.touchs(item_.bounds)){
                //Add it
                if(!this->nodes_[i]->hasChild(item_, true))
                    this->nodes_[i]->addChild(item_);
            }
        }//End of sub-node iterating
    }else{
        //No Subtrees
        //Test child count vs max_child
        if((this->children_.size() + 1u) > this->Max_Children &&
           this->Max_Children != 0u){//0u is inf
            //Out of Bounds(children)
            //Test if split or add anyway(optional?)
            if((this->layer_ + 1u) > this->Max_Layers &&
               this->Max_Layers != 0u){//0u is inf
                //Out of Bounds(Layers)
                //Can't subdivide further so just add child anyway
                if(!this->hasChild(item_, false))
                    this->children_.push_back(item_);
            }else{
                //Within Layer Bounds
                this->split();
                //Re-execute method
                this->addChild(item_);
            }
        }else{
            //Within child bounds
            if(!this->hasChild(item_, false))
                this->children_.push_back(item_);
        }
    }
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::addChild(Box<T, dimensions> bounds, void* child_){
    this->addChild(&bounds, child_);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::addChild(Box<T, dimensions>* bounds, void* child_){
    //Validate
    if(bounds == nullptr){
        std::cerr << "[ERROR]: AddChild Bounds are undefined!\n";
        return;
    }
    //Local Variables
    CollisionTreeItem nextItem;
    //Process
    nextItem.bounds = ((bounds != nullptr) ? (*bounds) : Box<T, dimensions>());
    nextItem.child = child_;
    this->addChild(nextItem);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions> bounds, std::vector<CollisionTreeItem>* buffer){
    this->query(&bounds, buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions> bounds, std::vector<Box<T, dimensions> >* b_buffer, std::vector<void*>* c_buffer){
    this->query(&bounds, b_buffer, c_buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions> bounds, std::vector<Box<T, dimensions> >* buffer){
    this->query(&bounds, buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions> bounds, std::vector<void*>* buffer){
    this->query(&bounds, buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions>* bounds, std::vector<CollisionTreeItem>* buffer){
    //Validate
    if(bounds == nullptr){
        std::cerr << "[ERROR]: Query bounds are undefined!\n";
        return;
    }
    if(buffer == nullptr){
        std::cerr << "[ERROR]: Query has an undefined buffer!\n";
        return;
    }
    //Local Variables
    //Process
    if(this->bounds_.touchs(bounds) && this->hasChildren()){
        //!In Range
        buffer->insert(buffer->begin(),
                       this->children_.begin(),
                       this->children_.end());
    }
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        this->nodes_[i]->query(bounds, buffer);
    }
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions>* bounds, std::vector<Box<T, dimensions> >* b_buffer, std::vector<void*>* c_buffer){
    //Validate
    if(c_buffer == nullptr && b_buffer == nullptr){
        std::cerr << "[ERROR]: Query has undefined buffers!\n";
        return;
    }
    //Local Variables
    std::vector<CollisionTreeItem> item_buffer = std::vector<CollisionTreeItem>();
    //Process
    this->query(bounds, &item_buffer);
    //Finish
    for(size_t i = 0u; i < item_buffer.size(); i++){
        if(b_buffer != nullptr)
            b_buffer->push_back(item_buffer[i].bounds);
        if(c_buffer != nullptr)
            c_buffer->push_back(item_buffer[i].child);
    }
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions>* bounds, std::vector<Box<T, dimensions> >* buffer){
    this->query(bounds, buffer, nullptr);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::query(Box<T, dimensions>* bounds, std::vector<void*>* buffer){
    this->query(bounds, nullptr, buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::debug(std::ostream* os_){//!Temporary(?)
    //!TODO
    //Validate
    if(os_ == nullptr)os_ = (std::ostream*)&std::cout;
    //Process
    (*os_) << "[INFO]: Starting debug of CollisionTree @ " << (this) << "\n";//!Debugging
    (*os_) << "[INFO]: Has Children: " << ((this->hasChildren()) ? ("true") : "false") <<
        "\tChild Count(0): " << ((this->hasChildren()) ? this->childCount(false) : 0u) <<
        "\tChild Count(1): " << ((this->hasChildren()) ? this->childCount(true) : 0u) <<
        "\n";//!Debugging
    (*os_) << "[INFO]:      Is Leaf: " << ((this->isLeaf()) ? "true" : "false") <<
        "\tHas Subtrees  : " << ((this->hasSubtrees()) ? "true" : "false") << "\n";//!Debugging
    (*os_) << "[INFO]: Node Count(0): " << ((this->hasSubtrees()) ? this->nodeCount(false) : 0u) << "\tNode Count(1): " << ((this->hasSubtrees()) ? this->nodeCount(true) : 0u) << "\n";//!Debugging
    (*os_) << "[INFO]: Node Bounds: " << (this->bounds_) << "\n";//!Debugging//!TODO
    for(size_t n = 0u; n < 20u; n++)this->bounds_.debug(os_);
    for(size_t i = 0u; i < this->children_.size(); i++){
        (*os_) << "[INFO]: Starting Debugging Children[" << i << "]: \n";//!Debugging
        (*os_) << "[INFO]: Child Address: " << this->children_[i].child << "\n";//!Debugging
        (*os_) << "[INFO]: Child Bounds: " << (this->children_[i].bounds) << "\n";//!Debugging//!TODO
        (*os_) << "[INFO]: Finished Debugging Children[" << i << "].\n";//!Debugging
    }
    for(size_t i = 0u; i < this->nodes_.size(); i++){
        if(this->nodes_[i] == nullptr){
            (*os_) << "[WARNING]: NULLPTR SubNode Detected[" << i << "]!!!\n";//!Debugging
            continue;
        }
        (*os_) << "[INFO]: Starting Debugging SubNode[" << i << "] @ " << (&nodes_[i]) << "\n";
        this->nodes_[i]->debug(os_);//!Debugging
        (*os_) << "[INFO]: Finished Debugging SubNode[" << i << "] @ " << (&nodes_[i]) << "\n";
    }
    (*os_) << "[INFO]: Finished debug of CollisionTree @ " << (this) << "\n";//!Debugging
}
//Private Static
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::subdivide(Box<T, dimensions> bounds, size_t parts, std::vector<Box<T, dimensions> >* buffer){
    CollisionTree<T, dimensions>::subdivide(&bounds, parts, buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::subdivide(Box<T, dimensions>* bounds, size_t parts, std::vector<Box<T, dimensions> >* buffer){
    //Validate
    if(bounds == nullptr || buffer == nullptr || parts == 0u)return;
    //Local Variables
    Point<T, dimensions> fractions = Point<T, dimensions>();
    Point<T, dimensions> p1 = Point<T, dimensions>(), p2 = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        fractions.setValue(i, (T)(bounds->getDimensionSize(i) / parts));
    for(size_t y = 0u; y < parts; y++){
        for(size_t x = 0u; x < parts; x++){
            for(size_t i = 0u; i < dimensions; i++){
                p1.setValue(i, (x * fractions.getValue(i)));
                p2.setValue(i, (x * fractions.getValue(i)) + fractions.getValue(i));
            }
            buffer->push_back(Box<T, dimensions>(p1, p2));
        }
    }
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::subdivide(Box<T, dimensions> bounds, size_t parts, std::vector<Box<T, dimensions>* >* buffer){
    CollisionTree<T, dimensions>::subdivide(&bounds, parts, buffer);
}
template<typename T, size_t dimensions>
void CollisionTree<T, dimensions>::subdivide(Box<T, dimensions>* bounds, size_t parts, std::vector<Box<T, dimensions>* >* buffer){
    //Validate
    if(bounds == nullptr || buffer == nullptr || parts == 0u)return;
    //Local Variables
    Point<T, dimensions> fractions = Point<T, dimensions>();
    Point<T, dimensions> p1 = Point<T, dimensions>(), p2 = Point<T, dimensions>();
    //Process
    for(size_t i = 0u; i < dimensions; i++)
        fractions.setValue(i, (T)(bounds->getDimensionSize(i) / parts));
    for(size_t y = 0u; y < parts; y++){
        for(size_t x = 0u; x < parts; x++){
            for(size_t i = 0u; i < dimensions; i++){
                p1.setValue(i, (x * fractions.getValue(i)));
                p2.setValue(i, (x * fractions.getValue(i)) + fractions.getValue(i));
            }
            buffer->push_back(new Box<T, dimensions>(p1, p2));
        }
    }
}

#endif // COLLISIONTREE_CPP_
