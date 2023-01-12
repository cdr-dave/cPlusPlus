//
//  main.cpp
//  返回值优化
//
//  Created by cdr on 2022/5/11.
//


#include <iostream>

using namespace std;

// Can copy and move
class A {
public:
  A() { cout << "Create A\n"; }
  ~A() { cout << "Destroy A\n"; }
  A(const A&) { cout << "Copy A\n"; }
  A(A&&) { cout << "Move A\n"; }

    int in = 0;
    void print() {
        cout << in << endl;
    }
    
    void add() {
        in++;
    }
    
    void printTest() const {
        cout << "printTest" << endl;
    }
    
    void otherTest() {
        int a = 0;
        a++;
    }
};

A getA_unnamed()
{
  return A();
}

void callAFunc(A a) {//本身就调用拷贝构造函数
    cout << "callAFunc" << endl;
    a.print();
}

void callAFunc2(const A& a)//没有构造
{
    cout << "const callAFunc&" << endl;
    a.printTest();//'this' argument to member function 'printTest' has type 'const A', but function is not marked const
    //const 对象只能调用 const 方法
}

void callAFunc3(A& a)
{
    a.in = 100;
}

A resetA()
{
    auto a = A();
    a.in = 300;
    cout << "函数直接值传递：没有优化" << endl;
    callAFunc(a);//拷贝构造函数，不过不影响外面 a 的返回值优化
    cout << "......." << endl;
    
    callAFunc2(a);
    callAFunc3(a);
    a.add();
    a.print();
    a.print();
    a.printTest();
    a.otherTest();
    return a;
}
//
//struct obj {
//    obj() {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }
//    
//    obj(obj&&) {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }
//    
//    obj(const obj&) {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }
//}
//

int main()
{
  auto a = getA_unnamed();
    cout << "测试返回值优化：当数值行其他操作时，不影响优化：" << endl;
    A b = resetA();
    /*
     Create A
     Destroy A
     
     返回非引用类型的表达式结果是个纯右值（prvalue）。在执行 auto r = … 的时候，编译器会认为我们实际是在构造 matrix r(…)，而“…”部分是一个纯右值。因此编译器会首先试图匹配 matrix(matrix&&)，在没有时则试图匹配 matrix(const matrix&)；也就是说，有移动支持时使用移动，没有移动支持时则拷贝
     ——
     返回值优化（拷贝消除）
     
     虽然 GCC 和 Clang 的结果完全不变，但 MSVC 在非优化编译的情况下产生了不同的输出（优化编译——使用命令行参数 /O1、/O2 或 /Ox——则不变）：Create AMove ADestroy ADestroy A也就是说，返回内容被移动构造了。
     
     */
}
