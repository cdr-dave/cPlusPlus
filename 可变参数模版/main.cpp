//
//  main.cpp
//  可变参数模版
//
//  Created by cdr on 2022/5/21.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <string>

class Obj_0 {
public:
    Obj_0() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Obj_0(Obj_0&& obj) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Obj_0(const Obj_0& obj) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Obj_1 {
public:
    Obj_1(int parame) {
        std::cout << __PRETTY_FUNCTION__ << ": parame is " << parame << std::endl;
    }
    
    Obj_1(Obj_0&& obj) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Obj_1(const Obj_0& obj) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};


//工具模版转发构造不定参
template<typename T, typename... Args> ///模版编译展开也是普通函数，也就有 nrvo
T CreateObj(Args&&... args) {
    return T(std::forward<Args>(args)...);
}


//template<class T>
//constexpr typename std::enable_if<std::is_arithmetic<T>::value, T>::type sum(T x) {
//    return x;
//}
//
//template<class T, class... Args>
//constexpr typename std::enable_if<std::is_arithmetic<T>::value, T>::type sum(T x, Args... args) {
//    return x + sum(std::forward<Args>(args)...);
//}

template<class T>
auto sum(T x) {
    return x;
}

//模版递归
template<class T, class... Args>
auto sum(T x, Args... args) {
    return x + sum(std::forward<Args>(args)...);
}
    
//闭包函数器
template<class F, class... Args>
auto compose(F&& f, Args&&... other) {
    
    return [&f, &other...](auto&&... x) {
        return f(std::forward<Args>(other)...)(std::forward<decltype(x)>(x)...);
    };
}

using num_type = std::tuple<std::string, int, std::string>;

std::ostream& operator<<(std::ostream& out, const num_type& data) {
    out << std::get<0>(data)
    << std::get<1>(data)
    << std::get<2>(data);
    
    return out;
}

int main(int argc, const char * argv[]) {
    /*
     Obj_0::Obj_0()
     Obj_1::Obj_1(int): parame is 12
     */
    Obj_0 obj0 = CreateObj<Obj_0>();
    Obj_1 obj1 = CreateObj<Obj_1>(12);
    std::cout << "===============" << std::endl;
    std::cout << sum(2.03, 4, 6) << std::endl;
//    std::cout << sum("a", "c") << std::endl;
    std::vector<num_type> arr = {
        {"aaa", 1111, "ad啊"},
        {"bbb", 2, "ac啊"},
        {"ccc", 44, "ab啊"},
    };
    
    std::get<2>(arr[1]) = "bb啊";
    
    auto [_, index, name] = (arr[1]);//类似的，可以在函数返回中体现，多参数回调
    std::cout << name << std::endl;
    std::cout << std::get<int>(arr[1]) << std::endl;//只有一个类型的时候，可以用类型获取
//    std::cout << std::get<std::string>(arr[1]) << std::endl; //string 有两个不行
    
    for (const auto& data : arr) {
        std::cout << data << std::endl;
    }
    
    // 输出多元组项数
    constexpr auto size = std::tuple_size_v<num_type>;
    std::cout << "Tuple size is " << size << std::endl;
    
    return 0;
}
