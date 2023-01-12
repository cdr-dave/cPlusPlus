//
//  main.cpp
//  多态
//
//  Created by cdr on 2022/5/12.
//

#include <iostream>
/*
//重载测试
 1. 父类 function 不是虚函数，那么bp 只能调用到父类的 function 不管子类是否有同名同参数的函数
 2. 父类 function 是虚函数，子类有同名同参数方法，触发重写机制，运行时多态，调用子类function
 3. 父类function 是虚函数， 子类有同名不同参数方法，bp 指针 只能调用 父类 function 方法
 
class Base {
public:
    virtual void func() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Child : public Base {
public:
    void func(int a) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

 Base b;
 Child c;
 Base* bp = new Child();
 
 b.func();
 c.Base::func();
//    c.func(); err
 c.func(20);
 bp->func();
//    bp->func(20); err
 
*/
int main(int argc, const char * argv[]) {
    // insert code here...
    int* in = new int[2];
    __asm__("");
    in[0] = 22;
    in[2] = 44;
    __asm__("");
    size_t* ip = (size_t*)in - 1;
    delete[] in;
    __asm__("");
    return 0;
}
