//
//  main.cpp
//  调用堆栈
//
//  Created by cdr on 2022/5/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <thread>
#include <execinfo.h>

#define MAX_LEVEL 4

/*
 * dump 堆栈信息
 
 backtrace的实现依赖于栈指针（fp寄存器），在gcc编译过程中任何非零的优化等级（-On参数）或加入了栈指针优化参数-fomit-frame-pointer后可能不能正确得到程序栈信息
 backtrace_symbols的实现需要符号名称的支持，在gcc编译时需要加入-rdynamic参数
 内联函数没有栈帧，它在编译过程中被展开在调用位置
 尾调用优化Tail-Call Optimization将复用当前函数栈而不再生成新的函数栈，这将导致栈信息不能被正确获取
 
 * */
void DumpTraceback(int signal) {
    const int size = 200;
    void *buffer[size];
    char **strings;
    
    int nptrs = backtrace(buffer, size);
    printf("backtrace() returned %d address\n", nptrs);

    // backtrace_symbols函数不可重入， 可以使用backtrace_symbols_fd替换
    strings = backtrace_symbols(buffer, nptrs);
    if (strings) {
        for (int i = 0; i < nptrs; ++i) {
            printf("%s\n", strings[i]);
        }
        free(strings);
    }
}

void sigfunc(int signo) {
    printf("%s(0): %p\n", __func__, __builtin_return_address(0));
    printf("%s(1): %p\n", __func__, __builtin_return_address(1));
    printf("%s(2): %p\n", __func__, __builtin_return_address(2));
    printf("%s(3): %p\n", __func__, __builtin_return_address(3));
    printf("%s(4): %p\n", __func__, __builtin_return_address(4));
    
    exit(1);
}

namespace std {
int b() {
    printf("%s(0): %p\n", __func__, __builtin_return_address(0));
    
    while (1) {
//        sleep(1);
            this_thread::sleep_for(1s);
    }
}

}

int a(int temp) {
    temp += 1;
    printf("%s(0): %p\n", __func__, __builtin_return_address(0));
    
    DumpTraceback(32);
    return temp;
}

int c(int temp) {
    temp++;
    printf("%s(0): %p, %s\n", __func__, __builtin_return_address(0), static_cast<char*>(__builtin_return_address(0)));
    
    a(123);
    
    return temp;
}

#define _FILE_NAMES_LEN_ 255

class Debug_new_Obj {
public:
    Debug_new_Obj(const )
};

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    c(123);
//    sigfunc(2);
    return 0;
}
