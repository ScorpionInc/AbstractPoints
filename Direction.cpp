//Templated
#ifndef DIRECTION_CPP_
#define DIRECTION_CPP_

#include "Direction.hpp"
using namespace scorpion::util;

//Variables
//Constructors
template<uint64_t directions>
Direction<directions>::Direction() : data_(){
}
template<uint64_t directions>
Direction<directions>::Direction(std::vector<Byte>& buffer, bool bigBitEdien) : data_(){
}
template<uint64_t directions>
Direction<directions>::Direction(std::vector<bool> buffer_, bool bigBitEdien) : data_(){
}
template<uint64_t directions>
Direction<directions>::~Direction(){
}

//Functions
template<uint64_t directions>
bool Direction<directions>::hasDirection(){
}
template<uint64_t directions>
bool Direction<directions>::hasDirection(uint64_t direction){
}

//Methods

#endif//DIRECTION_CPP_
