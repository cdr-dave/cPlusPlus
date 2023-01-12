//
//  main.cpp
//  打印函数类型
//
//  Created by cdr on 2022/7/26.
//

#include <iostream>
#include "out_type.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Type_Out_N::out_type();

    Type_Out_N::out_type<0, int>();

    Type_Out_N::out_type<0, int, double, char>();
    
    std::cout << Type_Out_All::out_type() << std::endl;
    std::cout << Type_Out_All::out_type<int>() << std::endl;
    std::cout << Type_Out_All::out_type<float, int>() << std::endl;
    std::cout << Type_Out_All::out_type<float, int, double, char, char>() << std::endl;
    
    return 0;
}
