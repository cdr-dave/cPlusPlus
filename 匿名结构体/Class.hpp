//
//  Class.hpp
//  匿名结构体
//
//  Created by cdr on 2022/10/30.
//

#ifndef Class_hpp
#define Class_hpp

#include <iostream>
#include <stdio.h>

using namespace std;

class Func {
public:
     auto getData();
    
//    ostream& out(ostream& o) {
//        o << getData().d << std::endl;
//        
//        return o;
//    }
    
    
    static auto getData2()
    {
        //    struct {double d, int i, std::string str, char ch};
        //    return { 4.0, 3, "my str", 'c' }; // Cannot deduce return type from initializer list
    //    return struct { 4.0; 3; "my str"; 'c'; }; //Expected expression
        
        //    const struct { double d, int i, std::string str, char ch } ret = { 4.0, 3, "my str", 'c' };
        //    return ret;
        
        const struct { double d; int i; char c; } result = {
            10.555,
            12,
            'b'
        };
        
        return result;
    }
};

#endif /* Class_hpp */
