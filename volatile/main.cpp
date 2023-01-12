//
//  main.cpp
//  volatile
//
//  Created by cdr on 2022/5/7.
//
/*
 表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。遇到这个关键字声明的变量，
 编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。声明时语法：int volatile vInt;
 当要求使用 volatile 声明的变量的值的时候，系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存
 */

#include <iostream>

//extern  int input,result;

//extern "C" {
//#include "testAsm.h"
//
//int testAsm() {
//    __asm__ __volatile__ ("movl %1,%0" :"=r" (result) : "r" (input));
//
//    return input;
//}

//}

using namespace std;

//static unsigned long read_p15_c1(void) {
//    unsigned long value;
//    __asm__ __volatile__(
//                         "mrc p15, 0, %0, c1, c0, 0 @ read control reg\n"
//                         : "=r"(value)//@编译器选择一个R*寄存器
//                         :
//                         : "memory");
//#ifdef MMU_DEBBUG
//    printf("p15/c1 is = %08lx\n", value);
//#endif
//
//    return value;
//}
//
//static void write_p15_c1(unsigned long value)
//{
//#ifdef MMU_DEBUG
//        printf("write %08lx to p15/c1\n", value);
//#endif
//        __asm__ __volatile__(
//                        "mcr p15, 0, %0, c1, c0, 0 @ write it back\n"
//                        :
//                        : "r" (value) //@编译器选择一个R*寄存器
//                        : "memory");
//        read_p15_c1 ();
//}


//extern int input,result;
//
// void test_at_t()
// {
//        result  = 0;
//        input  = 1;
//        __asm__
//    __volatile__("add %2,%0":"=r"(result):"0"(result),"m"(input));
//
// }



int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
//    test_at_t();
    int i = 9;
    int a = i;

    cout << "i = " <<  a << endl;

//    write_p15_c1(1223L);
//    __asm__("movl -0x14(%rbp), 20h");
//    testAsm();
//    __asm__ __volatile__ ("movl %1,%0" :"=r" (result) : "r" (input));
//    extern "C" {
//    __asm { mov dword ptr [rbp-0x14], 20h }
//    __asm__ ("mov %0, 20"
//                         :"=r"(i) // 5
//                         :"r"(i));
//    unsigned foo = 22;
//        __asm__ __volatile__("mov %0, 1"
//                             :"=r"(foo) // 5
//                             :"r"(foo)
//                             );
//    }

    __asm__("");
//    __asm {
//        mov i, 20h
//    }

    int b = i;

    cout << "i = " <<  b << endl; //debug 32, release
//
    return 0;
}

//unsigned int arrayA[10] = { 0x22, 0x12,0,0,0,0,0,0,0};
//int main() {
//
//
//  __asm__ goto volatile (
//                "jp %l[label]\n"
//                : /*no output*/
//                : [my_op1] "r" (arrayA[0]),[my_op2] "r" (arrayA[1])
//                : /*no cobblers*/
//                : label
//        );
//
//
//  return 0;
//
//label:
//
//  __asm__ volatile (
//                "add %[my_out], %[my_op1], %[my_op2]\n"
//                : [my_out] "=&r" (arrayA[3])
//                : [my_op1] "r" (arrayA[0]),[my_op2] "r" (arrayA[1])
//        );
//
//
//  return 0;
//
//}
