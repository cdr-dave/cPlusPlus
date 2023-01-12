//
//  includeTest.hpp
//  头文件包含问题
//
//  Created by cdr on 2022/6/8.
//

#ifndef includeTest_hpp
#define includeTest_hpp

#include <stdio.h>

//void testFunc_h() { //有对应。cpp 当 include 时，出现重复定义
//    printf("%s\n", __PRETTY_FUNCTION__);
//}

inline void testFunc_inline_h() {
    printf("%s\n", __PRETTY_FUNCTION__);
}

void testFunc_cpp();

#endif /* includeTest_hpp */
