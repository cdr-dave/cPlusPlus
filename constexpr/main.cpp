//
//  main.cpp
//  constexpr
//
//  Created by cdr on 2022/5/17.
//

#include <stdio.h>
#include <array>


#include <iostream>
#include <vector>


int sqr(int n)
{
    return n * n;
}

constexpr int sqr_c(int n) {
    return n*n;
}

static int sqr_s(int n) {
    return n * n;
}


constexpr int factorial(int n)
{
//    printf("...");
//    static_assert(n == 12, "...");//Static_assert expression is not an integral constant expression
    if (n >= 12 || n < 0) {
        std::invalid_argument("....ffff");
    }
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}


struct magic {
//  static const int number = 42;//error 改成 static inline const int number = 42; 这是因为 ODR-use 的类静态常量也需要有一个定义，在没有内联变量之前需要在某一个源代码文件（非头文件）中这样写：const int magic::number = 42;
    static constexpr int number = 44;
    static const int number_sc = 11;
//    static int n2 = 43;//Non-const static data member must be initialized out of line
    const int n3 = 11;
    
};
/*
 上面的问题 也可以在 类/结构体 外面 加 const int magic::number = 42; 定义
 类的静态 constexpr 成员变量默认就是内联的。const 常量和类外面的 constexpr 变量不默认内联，需要手工加 inline 关键字才会变成内联。
 为什么需要内联 或者说静态变量定义，不需要 写在外部了
 */


//template <class T>
//inline constexpr bool
//  is_trivially_destructible_v =
//    is_trivially_destructible<
//      T>::value;

constexpr int aa = 42;
void callConsteexpr() {
//    constexpr int a = 42;
//
//    constexpr const int& b = a;//Constexpr variable 'b' must be initialized by a constant expression
}

//constexpr void callConsteexpr_2() {
//        constexpr int a = 42;
//
//        constexpr const int& b = a;//Constexpr variable 'b' must be initialized by a constant expression
//}

class ConstexprClass {
public:
    constexpr ConstexprClass() {
        
    }
    
    
};

int main()
{
    //内联
    std::vector<int> v;
    // 调用 push_back(const T&)
    v.push_back(magic::number);
    
    std::cout << v[0] << std::endl;
    
//    magic mc;
//    v.push_back(mc.number_sc); //失败，也还是需要内联或者外部定义
//    std::cout << v[1] << std::endl;
    
    
    int n = sqr(4);
//    int ar2[n] = {};//err
    int ar2[n];// 查看汇编知道，初始化的时候有具体调用大小 作为 leaq 的数值， 单纯申明，没啥问题，不过，耶没什么用处，因为赋值，会产生不确定的内存泄漏
    constexpr int n1 = sqr_c(4);
    int a[n1] = {};
//    std::array<int, n> arr;//这个倒是可以直接报错处理
    std::array<int, n1> arr;
    static int n2 = sqr(4);
    static int n3 = sqr(3);
    static int n4 = sqr_s(3);
    
    
    constexpr int c1 = factorial(10);
    constexpr int c2 = factorial(0);
    printf("%d, %d \n", c1, c2);
//    constexpr int c2 = factorial(20);
    
    //int a2[n2] = {};//Variable-sized object may not be initialized
//    printf("%d\n", a[0]);
    
//    constexpr int aa = 42;//如果放在这里，下面会报错 Constexpr variable 'bb' must be initialized by a constant expression

    callConsteexpr();
    //    constexpr  int& bb = aa;//Binding reference of type 'int' to value of type 'const int' drops 'const' qualifier
    constexpr const int& bb = aa;
    
    
    ConstexprClass cc;
}

//#include <stdio.h>
//
//int sqr(int n)
//{
//    return n * n;
//}
//
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//
//    int arr[100] = {0};
//    __asm__("");
//    int ar2[50];// = {}; //未初始化的数组，在汇编中，未做任何处理
//
//    __asm__("");
//    // ar2[6] = 12; //movl    $12, -600(%rbp)
//    // ar2[4] = 11;//movl    $11, -608(%rbp)
//    int n = sqr(2);
//    __asm__("");
//    int num = arr[sqr(2)];
//
//    __asm__("");
//    int n2 = ar2[0];
//
//    printf("%d, %d\n", num, n2);
//    // n2 = 11;
//    return 0;
//}
