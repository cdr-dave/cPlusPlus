//
//  main.cpp
//  匿名结构体
//
//  Created by cdr on 2022/10/30.
//

#include <iostream>
#include "Class.hpp"
#include <cstdio>

auto FuncToStru(int n)
{
    struct { double d; int i; char c; } ret = {
        4.0,
        n + 3,
        'a',
    };
    
    return ret;
}

void CPPTest()
{
    auto data = FuncToStru(3);
//    stringstream str;
    std::cout << "data is " << data.d << ", " << data.i << ", " << data.c << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    CPPTest();
        
    Func func;
//    auto data = func.getData(); //Function 'getData' with deduced return type cannot be used before it is defined
//    std::cout << data.d << std::endl;
    auto data2 = func.getData2();
    std::cout << data2.d << std::endl;
    
    return 0;
}
