//
//  main.cpp
//  constexpr使用
//
//  Created by cdr on 2022/5/12.
//

#include <iostream>
#include <stdio.h>

struct A {
    void *p;
    constexpr A() : p(this) {
//        printf("A");
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

constexpr A g() {
    A a;
    return a;
}

constexpr A a; //如果我在 constexpr A() 构造函数中添加了 std::cout  这里竟然会报错 Constexpr variable 'a' must be initialized by a constant expression
const A b = g();

void h() {
    A c = g();
}

extern const A d;
constexpr A f() {// 类似的，加了打印 报错 Constexpr function never produces a constant expression
    A e;
    if (&e == &d) {
//        std::cout << __PRETTY_FUNCTION__ << "_1" << std::endl;
        return A();
    }
    else
    {
//        std::cout << __PRETTY_FUNCTION__ << "_2" << std::endl;
        return e;
    }
}

constexpr A d = f();

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
