/* Notes:
 * Version: 1.0.0.0
 * Authors: Scorpion Inc
 * Purpose: Serializable General Direction Class.
 * Last Updated: 20160118
 * Created: 20160118
 * TODO:
 * #1) Make a TODO list
//*/
#include <iostream>//!Debugging
#include <stdint.h>
#include <vector>

#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

typedef uint8_t Byte;
namespace scorpion{
namespace util{
    template<uint64_t directions>
    class Direction{
    public:
        static const uint64_t DIRECTIONS = directions;
        Direction();
        Direction(std::vector<Byte>& buffer, bool bigBitEdien = true);
        Direction(std::vector<bool> buffer_, bool bigBitEdien = true);
        ~Direction();
        bool hasDirection();
        bool hasDirection(uint64_t direction);
        void setAll(bool aFlag);
        void setDirection(uint64_t direction, bool aFlag = true);
        void serialize(std::vector<Byte>& buffer, bool bigBitEdien = true);
    protected:
        std::vector<Byte> data_;
    private:
    };
}
}

#endif//DIRECTION_HPP_
