//
//  Header.h
//  现代C++编程实战
//
//  Created by cdr on 2022/7/26.
//

#ifndef out_type_h
#define out_type_h

#include <string>
#include <type_traits>


#ifndef __MSC_VER
#include <cxxabi.h>
#endif

/*
 思考
 最开始是使用下面的方式
 
 template<typename R>
 void out_type() {
     std::cout << "=======" << std::endl;
     char * name = abi::__cxa_demangle(typeid(R).name(), nullptr, nullptr, nullptr);
     std::cout << name << std::endl;
     free(name);
 }

 template<typename R, typename... Args>
 void out_type() {
     out_type<R>();
     out_type<Args...>();
 }
 
 针对 out_type<int>();
 Call to 'out_type' is ambiguous
 二义性，测试
 template<typename... Args>
 void test() {
    //...
 }
 
 接受。test();//
 也就是 typenanme.. Args 是允许空的
 回到问题，首先确定的，逗号展开是不可能的了
 那么递归方式有没有余地呢？
 答案是可以的
 
 就是确保 递归终止模板与模板不冲突
 递归终止 试过 template<> void out_type() 发现不行
 那么改 考虑递归修改，认为 template<typename R, typename... Args>
 中 Args 为空，那么为了与递归终止不同，
 在递归里，再添加一个类型 T
 template<typename R, typename T, typename... Args>
 
 解决问题～
 这里有个小问题，就是 想要补充字段，确定是第几个参数 需要传值
 针对不定参，一般情况虽然可以放在 最右边 template<typename R, std::size_t I = 0>
 这样可以确保调用时候不传值
 但是，跟不定参数结合时

 out_type<T, Args..., i>(); //error 是不允许的, 奇特的是，i 是类型时却允许
 当然， i 值计算出来，也要。constexpr
 所以，衡量后，只能放在最左边，每次调用传 0
 
 
 依旧有问题，就是无法处理空的情况？
 答案是，什么都不给
 
 */

//不带数量版本
namespace Type_Out
{
    void out_type() {
        std::cout << "没有参数" << std::endl;
    }

    template<typename R>
    void out_type() {
        
#ifndef __MSC_VER
        char * name = abi::__cxa_demangle(typeid(R).name(), nullptr, nullptr, nullptr);
        std::cout << name << std::endl;
        free(name);
#else
        std::cout << typeid(R).name() << std::endl;
#endif
    }

    template<typename R, typename T, typename... Args>
    void out_type() {
        
        out_type<R>();
        out_type<T, Args...>();
    }
};

//带数量版本
namespace Type_Out_N
{
    void out_type() {
        std::cout << "没有参数" << std::endl;
    }

    template<std::size_t I, typename R>
    void out_type() {
        std::cout << "第 " << I << " 个参数类型" << std::endl;
        char * name = abi::__cxa_demangle(typeid(R).name(), nullptr, nullptr, nullptr);
        std::cout << name << std::endl;
        free(name);
    }

    template<std::size_t I, typename R, typename T, typename... Args>
    void out_type() {
        
        out_type<I, R>();
        constexpr std::size_t i = I + 1 + sizeof...(Args);
        out_type<i, T, Args...>();
    }
};

namespace Type_Out_All
{

//辅助空类，判空使用 因为普通的 std::is_void<> 不允许多个类型参数
//std::size_t I,  没啥用，只是偷懒，跟 Type_Out_N对应上
struct test_obj
{

};

std::string out_type() {
//    std::cout << "没有参数" << std::endl;
    
    return "没有参数";
}

//template<typename R, bool tag = true> //这里可以传参，来确定 是  out_type<int> 还是 out_type<int, float> 哪种
template<std::size_t I, typename R>
std::string out_type() {
    std::string strName;
    
#ifndef __MSC_VER
    char * name = abi::__cxa_demangle(typeid(R).name(), nullptr, nullptr, nullptr);
    strName = name;
    free(name);
#else
    strName = typeid(R).name();
#endif
    
    if constexpr (I == 0) {
        std::cout << "类型：" << strName << std::endl;
    }
    
    return strName;
    
}

template<std::size_t I, typename R, typename T, typename... Args>
std::string out_type() {
    
    auto strName = out_type<1, R>();
    if constexpr (std::is_constructible_v<test_obj, Args...>) {
//        std::cout << "空！！" << std::endl;
        strName = strName + std::string(" |+++| ") + out_type<1, T>();
    }
    else
    {
        strName = strName + std::string(" |+++| ") + out_type<1, T, Args...>();
//        std::cout << "非空!!" << std::endl;
    }
    
    if constexpr (I == 0) {
        std::cout << "类型：" << strName << std::endl;
    }
    
    return strName;
}

};

///
#endif /* out_type_h */
