//
//  main.cpp
//  编译期计算
//
//  Created by cdr on 2022/5/14.
//

#include <iostream>

typedef uint64_t C_SIZE;
//template<int n>
//struct functional {
//    static const int value = n * functional<n - 1>::value;
//};

// int -> 直接编译不过，传100， 因为是编译时结果 溢出 改成 factorial<10>也可以
template <C_SIZE n>
struct factorial {
//    static_assert(n >= 0, "Arg must be non-negative");
  static const C_SIZE value =
    n * factorial<n - 1>::value;
};

template<>
struct factorial<0> {
    static const C_SIZE value = 1;
};


template <bool condition,
          typename Body>
struct WhileLoop;

template <typename Body>
struct WhileLoop<true, Body> {
  typedef typename WhileLoop<
    Body::cond_value,
    typename Body::next_type>::type
    type;//递归
};

template <typename Body>
struct WhileLoop<false, Body> {
  typedef
    typename Body::res_type type;
};

template <typename Body>
struct While {
  typedef typename WhileLoop<
    Body::cond_value, Body>::type
    type;
};


template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant type;
};


template <int result, int n>
struct SumLoop {
  static const bool cond_value =
    n != 0;
  static const int res_value =
    result;
  typedef integral_constant<
    int, res_value>
    res_type;
  typedef SumLoop<result + n, n - 1>
    next_type;
};

template <int n>
struct Sum {
  typedef SumLoop<0, n> type;
};

//优先选择函数，再选择模版
void f(int i) {
    printf("%s\n", __PRETTY_FUNCTION__);
}

template<class T>
void f(T) {
    printf("template_%s\n", __PRETTY_FUNCTION__);
    
}


//void f(double) -> void f<int>;//函数没有推导指南

int main(int argc, const char * argv[]) {
    // insert code here...
    int v = factorial<100>::value;
    std::cout << v << std::endl;
    int vv = While<Sum<10>::type>::type::value;
    std::cout << vv << std::endl;
    
    f(32);
    f(33.0);
    
    return 0;
}
