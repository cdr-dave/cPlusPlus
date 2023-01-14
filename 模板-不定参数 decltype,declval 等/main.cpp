//
//  main.cpp
//  模板-不定参数 decltype / declval 等
//
//  Created by cdr on 2022/7/25.
//

#include <iostream>
#include <type_traits>
#include "out_type.h"

#ifndef __MSC_VER
#include <cxxabi.h>
#endif

//using namespace Type_Out_N;
using namespace Type_Out_All;


template<typename... Args, typename T>//, bool = std::is_void<Args...>::value>
//    static inline ret_type ptr(lambda_type& t) {
static auto ptr_2(T& t) {
    using R = decltype(std::declval<T>()(std::declval<Args>()...));
    out_type<0, R>();
    
    using RetType = R(*)(Args...);
    
    out_type<0, RetType>();
    
    RetType* ptr = nullptr;
    return ptr;
//    using RetType = R(*)(Args...);
//
//    return static_cast<RetType>(lambda_ptr_exe22<R, Args..., T>);
}

template<typename R, typename T, typename... Args, typename P>
void c_func(P&& ch) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    
    out_type<0, R, T, Args..., std::decay_t<P>>();//作为实际类型参数 是可以 放在容易位置，
//    out_type<0, T>();
//    constexpr auto n = sizeof...(Args);
//    out_type<Args..., index = n>();// 注意不定参写法，作为模板参数 类似的有 call(std::forward<Args>(args)...), (std::declval<Args>()...)
    using RetType = R(*)(Args...);//作为函数指针参数时，不定参写法
    auto size = sizeof...(Args);//size 的时候调用方式
    std::cout << "args size is " << size << std::endl;
    std::cout << "参数类型 " << std::endl;
    out_type<0, std::decay_t<P>>();//注意 && 右值类型引用， 最好还是 去除 const/volatile 引用，指针等
}

//template<typename T, typename ... Args> 注意顺序，否则就要手动写T类型
//反过来，如果确定类型 输入，就需要 先去定其他类型，再来确定 Args
template<typename ... Args, typename T>
 void func(T&& d) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
     c_func<int, double, std::string, char* ,float, Args...>('ch');
}

//
/*
想要判断 不定参是否为空，shiyong  std::void_v<Args...> 不行
 转个思路发现，不定参能用到的 有 is_constructible_v 是否构造
 定义辅助类 Test_Obj
 用来判断是 否作为构造参数 的参数
*/
struct Test_Obj
{

};

template<typename ... Args>
void j_void() {
    std::is_void_v<void>;
//    std::is_void_v<Args...>;// Too few template arguments for variable template 'is_void_v' 不允许多个参数
    
    if constexpr (std::is_constructible_v<Test_Obj, Args...>) {
        std::cout << "空！！" << std::endl;
    }
    else
    {
        std::cout << "非空!!" << std::endl;
    }
//    if (std::is_void_v<decltype(std::declval<Args>()...)>) {
//        std::cout << "空！！" << std::endl;
//    }
//    else
//    {
//        std::cout << "非空!!" << std::endl;
//    }
}

template<typename T, typename... Args, typename F> //这种情况，除非对应 void test_args(F&& f) 否则怎么都失败
//template<typename T, typename... Args>
//template<typename... Args, typename F>
//template<typename T, typename... Args> //这种，只要 test_args<int> 至少一个类型，都匹配
//void test_args() {
//void test_args(F&& f) {
//void test_args(Args&&... args, F&& f) {//不行，Args必须在最右侧
    void test_args(F&& f, Args&&... args) { //作为参数时候，使用自动推导，不要求跟上面模板类型顺序一一对应
//    void test_args(F* f = nullptr) {
//    out_type<0, T, Args..., F>();
//    out_type<0, T, Args...>();
        out_type<0, Args..., F>();
//        std::cout << args << std::endl;
}

template<typename T>
void printf(T value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Args>
void printf(T value, Args... args) {
    std::cout << value << std::endl;
    printf(args...);
}

int main(int argc, const char * argv[]) {
    // insert code here...

//    test_args();
//    test_args<int, bool>();
//    test_args<int, char>(true);
//    test_args<int, char>();
    
    printf(1, 2, "123", 1.1);
    
    test_args<float>(1, true);
    
    auto call22 = [](char*, double) ->int { return 32;};
    ptr_2<char*, double>(call22);

    func(2);
    func<int>(2);
    func<std::string,int>(2);
    
    std::cout << "=====" << std::endl;
    
    j_void();
    j_void<int>();
    j_void<int, double>();
    
    return 0;
}
