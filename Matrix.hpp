/* Notes:
 * Version: 1.0.0.0
 * Authors: Scorpion Inc
 * Purpose: Fixed Size Two Dimensional Matrix Template
 * Last Updated: 20160118
 * Created: 20160118
 * TODO:
 * #1) Make a TODO list
//*/

#include <iostream>//!For Debugging

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

namespace scorpion{
namespace geometry{
    template<typename T, size_t W_, size_t H_>
    class Matrix{
    public:
        static const size_t WIDTH_ = W_;
        static const size_t HEIGHT_ = H_;
        //static struct MATRIX_DIR {};
        /*
            size_t UP, UP_RIGHT, RIGHT,//!TODO
            DOWN_RIGHT, DOWN, DOWN_LEFT,
            LEFT, UP_LEFT;
        };//*///!TODO
        Matrix();
        ~Matrix();
        T at(size_t x, size_t y);
        void set(T v, size_t x, size_t y);
        //void roll_c(MATRIX_DIR dir_, size_t index_, size_t amount_);
        //void roll_r(MATRIX_DIR dir_, size_t index_, size_t amount_);
        void shift();
        //!Operator
        T* operator [] (size_t index_);
    protected:
        T* data_;
    private:
    };
}
}

#endif // MATRIX_HPP_
