//
//  ClassTest.hpp
//  返回值优化NVRO
//
//  Created by cdr on 2022/10/30.
//

#ifndef ClassTest_hpp
#define ClassTest_hpp

#include <iostream>
#include "Base.h"

//class ClassTest;
//
//class Base
//{
//public:
//    Base() {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
//    }
//    
//    Base(const Base& ob) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
//    }
//    
//    Base(Base&& ob) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
//    }
//    
//    static Base createTest0() {
//        Base d;
//        return d;
//    }
//    
//    static ClassTest createTest1() {
//        ClassTest d;
//        return d;
//    }
//};
//class Base;
class ClassTest : public Base
{
public:
    ClassTest() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    ClassTest(const ClassTest& ob) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    ClassTest(ClassTest&& ob) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};



#endif /* ClassTest_hpp */
