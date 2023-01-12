//
//  main.cpp
//  optional, variant, expected, Herbception
//
//  Created by cdr on 2022/5/23.
//

#include <iostream>
#include <optional>
#include <variant>
#include <exception>
//#include <tl/expected.hpp>
/*
 老于 Mojave 的 macOS 上编译含有 optional 或 variant 的代码
 
#if defined(__clang__) && defined(__APPLE__)
#include <__config>
#undef _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#undef _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS
#define _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#define _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS
#endif
*/
class Obj {
public:
    Obj() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Obj(int i, const std::string& str) : num(i), str(str) {
        std::cout << __PRETTY_FUNCTION__ << ": " << i << ", " << str <<std::endl;
    }
    
    Obj(const std::string& str) : str(str){
        std::cout << __PRETTY_FUNCTION__ << ": " << num << ", " << str <<std::endl;
    }
    
    Obj(Obj&& obj) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Obj(const Obj&) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    ~Obj() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    int num = 33;
    std::string str;
};


class Obj_d {
public:
    Obj_d() = delete;
    
    int num = 21;
};

int main(int argc, const char * argv[]) {
    /*
     不传递任何参数，或者使用特殊参数 std::nullopt（可以和 nullptr 类比），可以构造一个“空”的 optional 对象，里面不包含有效值。
     第一个参数是 std::in_place，后面跟构造 T 所需的参数，可以在 optional 对象上直接构造出 T 的有效值。
     如果 T 类型支持拷贝构造或者移动构造的话，那在构造 optional<T> 时也可以传递一个 T 的左值或右值来将 T 对象拷贝或移动到 optional 中。
     */
    std::optional<Obj> obj;
    if (!obj) {
        std::cout << "obj is null" << std::endl;
    }
    else
    {
        std::cout << "obj is'n null" << std::endl;
    }
    
    std::optional<Obj> obj1(std::nullopt);
    if (!obj1) {
        std::cout << "obj1 is null(std::nullopt)" << std::endl;
    }
    
    std::optional<Obj> obj2(std::in_place, 12, "str");
    if (obj2) {
        std::cout << obj2->num << ", " << obj2.value().str << std::endl;
        
//        std::optional<Obj> obj3(std::in_place, 44, "str3");
        
//        obj2.swap(obj);//error -> obj2 nad obj --> has_value
        
//        if (obj2){
//            obj2.swap(obj2);
//            if (obj2) {
//                std::cout << obj2->num << ", " << obj2.value().num << std::endl;
//            }
//        }
        obj2.emplace(333, "str333");
        obj2.reset();
    }
    
//    obj2.swap(obj);
    
//    Obj_d d; //error
    std::optional<Obj_d> do0;//此时未构造
    if (!do0) {//此时未构造
        std::cout << "Obj_d is null" << std::endl;
    }
    std::optional<Obj_d> do1(std::nullopt);//此时未构造
    if (do1.has_value()) {
        std::cout << "Obj_d has_value" << do1.value().num << std::endl;
    }
    
    Obj obj5 {"sssss"};
    
    std::variant<std::string, int, char> vv{  "Hello world"};
    std::cout << get<std::string>(vv) << std::endl;

//    std::variant<std::string, int, std::string>  v_obj { "vvvvvvvvvvv" };//No matching constructor for initialization of 'std::variant<std::string
//    std::cout << get<std::string>(vv) << std::endl;
    std::variant<float, double, Obj, int>  v_obj { std::string("vvvvvvvvvvv") }; // 如果。{"vvvvv"}  error
    std::cout << std::get<Obj>(v_obj).str << ", " << v_obj.index() << std::endl;
    
    return 0;
}
