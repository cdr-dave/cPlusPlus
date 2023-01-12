//
//  main.cpp
//  函数形参 不管调用多少次，都是同一块内存 
//
//  Created by cdr on 2022/5/18.
//

#include <stdio.h>
#include <thread>

//#include <iostream>
//#include <chrono>
//#include <complex>
//#include <string>
//#include <thread>
//
//#include <bitset>

using namespace std;

int * g_ptr = nullptr;
void p_print(int n, const int* cpn, int* pn, const int& cpp, bool isT = false) {
    if (!isT){
    static int* ptr = &n;
    g_ptr = ptr;
    }
    printf("%p, %p, %p, %p, %p\n", &n, &cpn, &pn, pn, &cpp);
}

class Obj {
public:
    Obj() {
        printf("Obj start\n");
    p_print(n, &n, &n, n);
    p_print(n2, &n2, &n, n);
    p_print(n, &n2, &n3, n);
        printf("Obj end\n");

    };

    int n = 1;
    int n2 = 2;
    int n3 = 3;

};

void intIntervalTest(int n) {
    printf("IntervalTest %d\n", n);
}

int main() {
//    signal(SIGABRT, SIG_IGN);
    std::this_thread::sleep_for(std::chrono::seconds(100));
    int n = 1;
    int n2 = 2;
    int n3 = 3;
    p_print(n, &n, &n, n);
    printf("g_ptr: %d\n", *g_ptr);
    intIntervalTest(21);
    printf("g_ptr: %d\n", *g_ptr);
    intIntervalTest(n);
    intIntervalTest(n);
    intIntervalTest(n2);
    intIntervalTest(33);
    printf("g_ptr: %d\n", *g_ptr);
    p_print(n2, &n2, &n, n);
    printf("g_ptr: %d\n", *g_ptr);
    p_print(n3, &n2, &n3, n);
    printf("g_ptr: %d\n", *g_ptr);
    printf("====================\n");
    Obj obj;
    Obj* op = new Obj();
    
    /*
     0x7ff7bfeff0ac, 0x7ff7bfeff0a0, 0x7ff7bfeff098, 0x7ff7bfeff18c, 0x7ff7bfeff18c
     g_ptr: 1
     IntervalTest 21
     g_ptr: 21
     IntervalTest 1
     IntervalTest 1
     IntervalTest 2
     IntervalTest 33
     g_ptr: 33//如果函数堆栈一直是同一块内存，那么此时 g_ptr 应该是 1 而不是 上一次函数的 n(%rsp) 未知的数值，可以大致得到结论，就是，函数申请的栈空间是惰性的，下次使用会覆盖上次函数的栈，即使两次不是同一个函数
     0x7ff7bfeff0ac, 0x7ff7bfeff0a0, 0x7ff7bfeff098, 0x7ff7bfeff18c, 0x7ff7bfeff18c
     g_ptr: 2
     0x7ff7bfeff0ac, 0x7ff7bfeff0a0, 0x7ff7bfeff098, 0x7ff7bfeff184, 0x7ff7bfeff18c
     g_ptr: 3
     ====================
     Obj start
     0x7ff7bfeff06c, 0x7ff7bfeff060, 0x7ff7bfeff058, 0x7ff7bfeff178, 0x7ff7bfeff178//连续使用的话，每个变量的地址都跟下次使用一一致
     0x7ff7bfeff06c, 0x7ff7bfeff060, 0x7ff7bfeff058, 0x7ff7bfeff178, 0x7ff7bfeff178////跟上次一致
     0x7ff7bfeff06c, 0x7ff7bfeff060, 0x7ff7bfeff058, 0x7ff7bfeff180, 0x7ff7bfeff178
     Obj end
     Obj start
     0x7ff7bfeff06c, 0x7ff7bfeff060, 0x7ff7bfeff058, 0x10501c160, 0x10501c160
     0x7ff7bfeff06c, 0x7ff7bfeff060, 0x7ff7bfeff058, 0x10501c160, 0x10501c160
     0x7ff7bfeff06c, 0x7ff7bfeff060, 0x7ff7bfeff058, 0x10501c168, 0x10501c160
     Obj end

    */
    
    printf("1 ----------\n");
    
//    std::this_thread::sleep_for(500ms);
    std::this_thread::sleep_for(2s);
    printf("2 主线程\n");
    p_print(n, &n, &n, n);
    printf("3其他线程\n");
    std::this_thread::sleep_for(1s);
    std::thread th(p_print, n, &n, &n, n, true);
    th.detach();
//    printf("4其他线程n");
//    std::thread th2(p_print, n, &n, &n, n, true);
//    th2.detach();
    std::this_thread::sleep_for(3s);
    printf("4 ----------\n");
    /*
     
     1 ----------
     2 主线程 //这里依旧是主线程的堆栈空间
     0x7ff7bfeff0ac, 0x7ff7bfeff0a0, 0x7ff7bfeff098, 0x7ff7bfeff18c, 0x7ff7bfeff18c
     3其他线程//这里就不一样了，每个线程具备自身的堆栈空间
     0x700009570edc, 0x700009570ed0, 0x700009570ec8, 0x7ff7bfeff18c, 0x105033678
     4 ----------
     */
    
}

