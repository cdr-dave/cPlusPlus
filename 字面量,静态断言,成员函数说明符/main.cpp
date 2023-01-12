//
//  main.cpp
//  字面量,静态断言,成员函数说明符
//
//  Created by cdr on 2022/5/9.
//

#include <iostream>
#include <chrono>
#include <complex>
#include <string>
#include <thread>

#include <bitset>

/*
 C++11 引入了自定义字面量，可以使用 operator"" 后缀 来将用户提供的字面量转换成实际的类型。C++14 则在标准库中加入了不少标准字面量。
 
 */
using namespace std;

namespace cdr_literal {

    struct length {
        double value;
        enum unit { metre, kilometre, millimetre, centimetre, inch, foot, yard, mile, };
        static constexpr double factors[] =
        {
            1.0, 1000.0, 1e-3,
            1e-2, 0.0254, 0.3048,
            0.91444, 109.344
        };
        
        explicit length(double v, unit u = metre) {
            value = v * factors[u];
        }
    };

    length operator+(length lhs, length rhs) {
        return length(lhs.value + rhs.value);
    }


    //唯一的限制是非标准的字面量后缀必须以下划线 _ 打头
    length operator"" _m(long double v)
    {
      return length(v, length::metre);
    }

    length operator""_cm(long double v)
    {
      return length(v, length::centimetre);
    }
}

//没有初始化的非静态 const 数据成员和引用类型数据成员会导致默认提供的默认构造函数被删除
class A {
public:
//    const int i;
//    int& a;
//    static const int i;
    const int i;
    int&a;
};

//非静态的 const 数据成员和引用类型数据成员会导致默认提供的拷贝构造函数、拷贝赋值函数、移动构造函数和移动赋值函数被删除。
//跟第一点区别在于，初始化后，依旧不能使用拷贝/移动
class B {
public:
    int b = 2;
//    B() {
//
//    }
    
    const int i = 22;//
//    const int i;//Constructor for 'B' must explicitly initialize the const member 'i'
};

//用户如果没有自己提供一个拷贝构造函数（必须形如 Obj(Obj&) 或 Obj(const Obj&)；不是模板），编译器会隐式声明一个。
//用户如果没有自己提供一个拷贝赋值函数（必须形如 Obj& operator=(Obj&) 或 Obj& operator=(const Obj&)；不是模板）
//值拷贝
class C {
public:
    int c;
    int* cp;//浅拷贝， cp = other.cp;//delete 多次
//    C() {}
//    C(C& co) {} //No matching constructor for initialization of 'C' 定义后，没法使用默认构造函数
    
    void newC(int num) {
//        delete cp;
        cp = new int(num);
    }
    
    ~C() {
//        delete cp;//浅拷贝 delete 多次
    }
    
};

//用户如果自己声明了一个移动构造函数或移动赋值函数，则默认提供的拷贝构造函数和拷贝赋值函数被删除。
//这种情况，不管有没有 D(){} 默认构造，D d(D()) 都能用，但是没啥用,无法调用对象对应成员 Parentheses were disambiguated as a function declaration ，因为没有赋值构造函数
//d1.newD(32);//error: Member reference base type 'D (D (*)())' is not a structure or union
//可以写成 D d(std::move(D()))  No matching constructor for initialization of 'D' 需要补充构造
class D {
public:
    D() {
        cout << __PRETTY_FUNCTION__ << endl;

    }
    
    D(D&& d) {
        cout << __PRETTY_FUNCTION__ << endl;
        
    }
    
    D& operator=(D&& d) {
        cout << __PRETTY_FUNCTION__ << endl;
        return *this;
    }
    
    void newD(int num) {
        cp = new int(num);
    }
    
    ~D() {
//        delete cp;
    }
    
private:
    int* cp;
};

//用户如果没有自己声明拷贝构造函数、拷贝赋值函数、移动赋值函数和析构函数，编译器会隐式声明一个移动构造函数
class E {
public:
    D ed;
};

class E1 {
public:
    E1() {}
    E1(const E1& e) {
        cout << __PRETTY_FUNCTION__ << endl;
        //        this->ed = std::move(e.ed); //const & 有递归性质，内部成员无法使用不一样的转化
    }
    
    D ed;
};

class E2 {
public:
    E2() {}
    E2(const E2& e) {
        cout << __PRETTY_FUNCTION__ << endl;
    }
    
//    E2(E2&& e) : ed(std::move(e.ed)) { //同理，初始化列表也有 递归性质， && 移动赋值，内部无法使用 拷贝赋值
//        cout << __PRETTY_FUNCTION__ << endl;
//    }
    E2(E2&& e) {
        cout << __PRETTY_FUNCTION__ << endl;
        this->ed = std::move(e.ed);
//        this->ed = (e.ed);//const & 有递归性质，内部成员无法使用不一样的转化 Object of type 'D' cannot be assigned because its copy assignment operator is implicitly deleted
    }
    
    D ed;
};

using namespace cdr_literal;

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "i * i = " << 1i * 1i << endl;//i * i = (-1, 0) 虚数
    cout << "waiting for 500ms" << endl;
    this_thread::sleep_for(500ms);//时间 s, ms, h
    std::cout << "Hello, World!"s.substr(0, 5) << endl;//
    
    auto ll = 1.0_m + 10.0_cm;
    
    std::cout << "custom literal: " << ll.value << endl;
    
    auto v8 = 0677;//447 0 -> 开头 跟 0-7 数字 八进制
    std::cout << v8 << ": " << oct << v8 << endl; // dec 十， hex 十六， oct 八
    
    cout << dec << endl; //需要还原,不然下面的 r_earth_equatorial 会有影响
    
    unsigned mask = 0b111000000;
    std::cout << bitset<20>(mask) << endl;//二进制 00000000000111000000 （20， 2 -》 00）
    
    /*
     数字分隔符
     //约定而已，并不强制
     十进制数字使用三位的分隔，对应英文习惯的 thousand、million 等单位。
     十进制数字使用四位的分隔，对应中文习惯的万、亿等单位。
     十六进制数字使用两位或四位的分隔，对应字节或双字节。
     二进制数字使用三位的分隔，对应文件系统的权限分组。
     */
    
    unsigned mask2 = 0b111'000'000;
    long r_earth_equatorial = 6'3782222'1372;
    double pi = 3.14159'26525'89793;
    const unsigned magic = 0x44'42'47'4E;
    
    cout << r_earth_equatorial << endl;// << ": " << oct << r_earth_equatorial << endl;
    
//    static_assert(false,
//      "Alignment must be power of two");// false -> show error
    
    /*
     ，编译器会隐式声明一个。用户如果自己声明了一个移动构造函数或移动赋值函数，则默认提供的拷贝构造函数和拷贝赋值函数被删除。用户如果没有自己声明拷贝构造函数、拷贝赋值函数、移动赋值函数和析构函数，编译器会隐式声明一个移动构造函数。用户如果没有自己声明拷贝构造函数、拷贝赋值函数、移动构造函数和析构函数，编译器会隐式声明一个移动赋值函数。
     */
    
//    A a;//没有初始化的非静态 const 数据成员和引用类型数据成员会导致默认提供的默认构造函数被删除。 //Call to implicitly-deleted default constructor of 'A'
    B b0, b1;
    b1.b = 77;
//    b0 = b1;//Object of type 'B' cannot be assigned because its copy assignment operator is implicitly deleted
    {
        C c0, c1;
        c1.c = 100;
        c1.newC(1008611);
        c0 = c1;//c0.c == 100
        cout << *c1.cp << "," << *c0.cp << endl;
    
    }
    
//    D d0;//No matching constructor for initialization of 'D'
    D d1( D() );//警告： Parentheses were disambiguated as a function declaration// 没啥用 没有调用 D() 也没有调用 D(&&) 因为缺少 D(const D&)
    //    d1.newD(32);//error: Member reference base type 'D (D (*)())' is not a structure or union
    D d11(std::move(D()));// D() 然后 D(&&)
//    D d2;
//    D d3(d2);
//    D d4 = std::move(d2);
    
    E e0(std::move(E()));//自动生成移动 ，调用了 D() 然后 D(&&)
    
    E1 e1(std::move(E1()));//E1(const E1&)
    
    E2 e2(std::move(E2()));//E2(E2&&) D &D::operator=(D &&)
    
    
    return 0;
}
