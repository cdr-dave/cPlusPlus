//
//  main.cpp
//  头文件包含问题
//
//  Created by cdr on 2022/6/8.
//

#include <iostream>
#include "includeTest.hpp"

class A {
public:
//    auto a = 32;
    int a = 32;
    
    auto cFunc() const {
        return a;
    }
    
    void func() {
        a++;
    }
};

const A& getA() {
    return A();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    A a;
    a.cFunc();
    a.func();
    auto b = getA();
    b.func();
    b.cFunc();
    
    const auto& c = getA();
//    c.func();
    c.cFunc();
    
//    decltype(auto) c = getA();
//    c.func();
//    c.cFunc();
    (void)0;
    std::cout << typeid(b).name() << std::endl;
//    std::cout << typeid(c).name() << std::endl;
    std::cout << "Hello, World!\n";
//    testFunc_h();// 重复定义
    testFunc_inline_h();//
    testFunc_cpp();
    return 0;
}
