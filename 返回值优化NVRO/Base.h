//
//  Base.h
//  现代C++编程实战
//
//  Created by cdr on 2022/10/30.
//

#ifndef Base_h
#define Base_h

#include <iostream>
//不需要 #include "ClassTest.h" 不然会有 在 ClassTest : pulic Base // error expected class name
class ClassTest;

class Base
{
public:
    Base() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Base(const Base& ob) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Base(Base&& ob) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    static Base createTest0() {
        Base d;
        return d;
    }
    
    static ClassTest createTest1(); //不需要头文件，前置申明即可
//    static ClassTest* createTest1();
    

//    static auto createTest1() { //前置申明始终只是声明，函数体本身还是无法放头文件的
////        ClassTest d;
//        return new ClassTest; // error 未定义类型
//    }
};

#endif /* Base_h */
