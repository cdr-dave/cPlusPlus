////
////  main.cpp
////  信号 Raise
////
////  Created by cdr on 2022/7/16.
////
/*
 注：无法在macOS 中测试，在linux 中可以F
 start test signal
 start loop
 please input sig:
 10
 get sig num 10, data is 10
 please input sig:
 101
 please input sig:
 12
 User defined signal 2
 */
#include <iostream>
#include <signal.h>

#define CUSTOM_TEST_SIG 10
#define CUSTOM_TEST_SIG2 101
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "start test signal\n";
    signal(CUSTOM_TEST_SIG, [](int data) {
        std::cout << "get sig num " << CUSTOM_TEST_SIG << ", data is " << data << std::endl;
    });


//    signal(CUSTOM_TEST_SIG2, [](int data) {
//        std::cout << "get sig num " << CUSTOM_TEST_SIG2 << ", data is " << data << std::endl;
//    });

    std::cout << "start loop" << std::endl;

    while (true) {
        int sigN = 0;
        std::cout << "please input sig: " << std::endl;
        std::cin >> sigN;

        raise(sigN);
    }
    return 0;
}

/* signal example */
//#include <stdio.h>      /* printf */
//#include <signal.h>     /* signal, raise, sig_atomic_t */
//
//sig_atomic_t signaled = 0;
//
//void my_handler (int param)
//{
//  signaled = 1;
//    printf("aaaa");
//}
//
//int main ()
//{
//  void (*prev_handler)(int);
//
//  prev_handler = signal (SIGINT, my_handler);
//
//  /* ... */
//  raise(SIGINT);
//  /* ... */
//
//  printf ("signaled is %d.\n",signaled);
//
//
//  return 0;
//}


