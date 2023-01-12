//
//  main.cpp
//  返回值优化NVRO
//
//  Created by cdr on 2022/5/3.
//
/*
 return 语句中，当操作数是拥有自动存储期的非 volatile 对象的名字，该名字不是函数形参或 catch 子句形参，且其具有与函数返回类型相同的类类型（忽略 cv 限定）时。这种复制消除的变体被称为 NRVO，“具名返回值优化 (named return value optimization)”。
 在对象的初始化中，当源对象是无名临时量且与目标对象具有相同类型（忽略 cv 限定）时。当无名临时量为 return 语句的操作数时，称这种复制消除的变体为 RVO，“返回值优化 (return value optimization)”。
 
 ??
 在协程中，可以消除将形参向协程状态内的复制/移动，只要除了对形参的构造函数与析构函数的调用被忽略以外，不改变程序的行为即可。这种情形可以在暂停点后始终不使用形参，或者整个协程状态本就始终不在堆上分配时出现。
 (C++20 起)
 ??
 
 在 C++11 之前，返回一个本地对象意味着这个对象会被拷贝，除非编译器发现可以做返回值优化（named return value optimization，或 NRVO），能把对象直接构造到调用者的栈上。从 C++11 开始，返回值优化仍可以发生，但在没有返回值优化的情况下，编译器将试图把本地对象移动出去，而不是拷贝出去。这一行为不需要程序员手工用 std::move 进行干预——使用 std::move 对于移动行为没有帮助，反而会影响返回值优化。
 */

#include <iostream>  // std::cout/endl
#include <utility>   // std::move
#include "Base.h"
#include "ClassTest.hpp"

using namespace std;
class Obj {
public:
  Obj()
  {
      ip = new int(33);
    cout << "Obj(): " << ip << endl;
  }
    
    /*
     
     如果注释了移动函数或者拷贝 会有默认的，那么本质上就没有实现移动或者拷贝 动态内存 就会调用两次析构函数
     同时没有NRVO 返回值优化，
     像下面 2，3，4 的情况，
     *** 1 ***
     Obj(): 0x101129040
     1: 0x101129040
     *** 2 ***
     Obj(): 0x101129460
     ~Obj 0x101129460
     2: 0x101129460
     *** 3 ***
     Obj(): 0x101128e50
     Obj(): 0x10110d190
     ~Obj 0x10110d190
     ~Obj 0x101128e50
     3: 0x101128e50
     *** 4 ***
     Obj(): 0x10110d290
     Obj(): 0x10110cc10
     ~Obj 0x10110cc10
     ~Obj 0x10110d290
     4: 0x10110d290
     ~Obj 0x10110d290
     ~Obj 0x101128e50
     ~Obj 0x101129460
     ~Obj 0x101129040
     
     */
  Obj(const Obj&) //添加delete 编译器不通过
  {
    cout << "Obj(const Obj&)" << ip
       << endl;
  }
  Obj(Obj&& o)//添加delete 编译器不通过 c++ 17 好像可以 https://zh.cppreference.com/w/cpp/language/copy_elision
  {
      ip = o.ip;
      o.ip = nullptr;
    cout << "Obj(Obj&&)" << ip << endl;
  }

//    Obj& operator=(Obj&& o) {
//
//            ip = o.ip;
//            o.ip = nullptr;
//          cout << "operator=(Obj&& o)" << ip << endl;
//        return *this;
//    }
    
    ~Obj()//要有析构函数
    {
        delete ip;
        cout << __FUNCTION__ << " " << ip << endl;
    }
    int * ip = nullptr;
};

//constexpr Obj ss() {
//    return Obj();
//}

Obj simple()
{
     Obj obj;
  // 简单返回对象；一般有 NRVO
  return obj;
}
Obj simple_with_move()
{
  Obj obj;
  // move 会禁止 NRVO
  return std::move(obj);
}
Obj complicated(int n)
{
  Obj obj1;
  Obj obj2;
  // 有分支，一般无 NRVO
  if (n % 2 == 0) {
    return obj1;
  } else {
    return obj2;
  }
}

Obj cc(int i) {
    return complicated(i);
}

struct C { /* ... */
    C() {
        cout << "C()" << endl;
    }
    
    C(C&&) {
        cout << "C&&" << endl;
        
    }
};

C f() {
    cout << "f()" << endl;
    return C();
}

struct D;
D g();

struct D : C {
    
    D(D&&) {
        cout << "D&&" << endl;
        
    }
    
    D() : C(f()) {
        cout << "D()" << endl;
        
    }    // 初始化基类子对象时无消除， C&& 存在
    D(int) : D(g()) {
        
            cout << "D(int)" << endl;
        
    } // 无消除，因为正在初始化的 D 对象可能是某个其他类的基类子对象
};

D g() {
    cout << "g()" << endl;
    return D();
}


struct A {
    void *p;
    constexpr A(): p(this) {
        cout << "A()" << endl;
    }
    
    constexpr A(A&&): p(this) {
        cout << "A(&&)" << endl;
    }
};
 
constexpr A ga()
{
    A a;
    return a;
}

constexpr A ga2()
{
//   A a;
   return A();
}

//constexpr A aa;//Constexpr variable 'aa' must be initialized by a constant expression

extern const A d;
constexpr A fa() {
    A e;
    if (&e == &d) {
        return A();
    }
    else
        return A();
}

//constexpr A d = fa();//Constexpr variable 'dd' must be initialized by a constant expression
/*
 注意：上述规则指定的不是优化：针对纯右值和临时量的 C++17 核心语言规定在本质上不同于之前的 C++ 版本：不再有临时量用于复制/移动。描述 C++17 语义的另一种方式是“传递未实质化的值”：返回并使用纯右值时不实质化临时量。
 
 g()
 f()
 C()
 C&&
 D()
 */

int main()
{
    {
        cout << "****0***" << endl;
//        auto s0 = ss();
  cout << "*** 1 ***" << endl;
  auto obj1 = simple();
    cout << "1: " << obj1.ip << endl;
  cout << "*** 2 ***" << endl;
  auto obj2 = simple_with_move();
    cout << "2: " << obj2.ip << endl;
  cout << "*** 3 ***" << endl;
  auto obj3 = complicated(42);
    cout << "3: " << obj3.ip << endl;
    cout << "*** 4 ***" << endl;
    auto obj4 = cc(42);
    cout << "4: " << obj4.ip << endl;
}
    cout << ".........." << endl;
    D d = g();
    {
        cout << "=============A ======" << endl;
        A gg = ga();
        cout << "==-=="<< endl;
        A ga = ga2();
//        constexpr A b = ga();//错误： b.p 会悬垂，并会指向有自动存储期的临时量
    }
    
    
    /*
     g()
     f()
     C()
     C&&
     D()
     
     如果调用D(int)
     g()
     f()
     C()
     C&&
     D()
     C()
     D&&
     D(int)
     
     */
/*
 
 */
    
    std::cout << " === --- ===" << std::endl;
    auto db_0 = Base::createTest0(); // Base()
    std::cout << " === --- ===" << std::endl;
    auto db_1 = Base::createTest1(); // Base()  ClassTest()
    std::cout << " === --- ===" << std::endl;
}
