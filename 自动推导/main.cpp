//
//  main.cpp
//  自动推导
//
//  Created by cdr on 2022/5/6.
//

#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <map>

using namespace std;


map<string, int> arr = {{"a", 12}, {"b", 33}};


template<typename  T>
struct MyObj {
    MyObj(T value) {
        cout << typeid(T).name() << endl;
    }
};

MyObj(int) -> MyObj<double>;//手工提供一个推导向导 接受int ,直接改道 double //推导指南

int m = 100;
int callData() {
    return m;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int a = 21;
    decltype(a) b = a;
    decltype((a)) c = a; // int & c = a;
//    decltype(auto) k = a;
//    decltype(callData()) k = callData();
    decltype(auto) k = callData(); //decltype(非纯右值表达式) =》 引用？？？但是这里怎么不行
    
    a = 22;
    k = 200;
    
    cout << a << "," << b << "," << c << "," << k << "," << m << endl;//22,21,22,200,100
    
    cout << std::is_reference<decltype(k)>::value << endl;//0
//    cout << std::is_reference<k> << endl;
    
    MyObj obj1(string("abbc"));
    MyObj obj2("abbc");
    MyObj obj3(32);// -> double
    MyObj obj4(32.0);
    
    auto iter = arr.find("a");
    auto [key, value] = arr.equal_range("a");
    
    return 0;
}
