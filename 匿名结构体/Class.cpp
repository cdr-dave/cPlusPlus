//
//  Class.cpp
//  匿名结构体
//
//  Created by cdr on 2022/10/30.
//

#include "Class.hpp"
#include <string>

auto Func::getData()
{
    //    struct {double d, int i, std::string str, char ch};
    //    return { 4.0, 3, "my str", 'c' }; // Cannot deduce return type from initializer list
//    return struct { 4.0; 3; "my str"; 'c'; }; //Expected expression
    
    //    const struct { double d, int i, std::string str, char ch } ret = { 4.0, 3, "my str", 'c' };
    //    return ret;
    
    const struct { double d; int i; char c; } result = {
        10.5,
        1,
        'z'
    };
    
    return result;
}
