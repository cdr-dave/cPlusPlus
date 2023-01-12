//
//  offset.c
//  volatile
//
//  Created by cdr on 2022/5/12.
//

#include <stdio.h>

//int main(void) {
////    unsigned value = 0;
////    __asm__ __volatile__(
////                         "mov %0, 1\n"
////                         "mov rax, offset 3f\n"
////                         "jmp rax\n"
////                         "mov %0, 2\n"
////                         "3:"
////                         : "=r" (value)
////                         :
//////                         : "rax"
////                         );
////    printf("%u\n", value);
//    unsigned foo = 10;
////    const int bar = 15;
//
//    __asm__ __volatile__("mov %0, 1"
//                         :"=r"(foo) // 5
//                         :"r"(foo)
//                         );
//    printf("%u\n", foo);
//    
//    return 0;
//}
