//
//  main.cpp
//  信号 alrm/setitimer
//
//  Created by cdr on 2022/7/18.
//

#include <iostream>
//#include <signal.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <time.h>
//#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//__BEGIN_DECLS
//extern "C" {

#include <time.h>
#include <sys/time.h>

void start_timer_test() {
    struct itimerval timeval;
    struct itimerval oldTimeval;
    
//    struct itimerval timeval2;
//    struct itimerval oldTimeval2;
//
//    struct itimerval timeval3;
//    struct itimerval oldTimeval3;
    
    //只设置 it_value 触发一次
    timeval.it_value.tv_sec = 5;//秒
    timeval.it_value.tv_usec = 0;//微妙 两个以最大数那个为基准
    
//
//    timeval2.it_value.tv_sec = 5;//秒
//    timeval2.it_value.tv_usec = 0;//微妙 两个以最大数那个为基准
//
//
//    timeval.it_value.tv_sec = 5;//秒
//    timeval.it_value.tv_usec = 0;//微妙 两个以最大数那个为基准
    
#if 1
    timeval.it_interval.tv_sec = 0;
    timeval.it_interval.tv_usec = 500000;// == 0.5
    
//    timeval2.it_interval.tv_sec = 0;
//    timeval2.it_interval.tv_usec = 500000;// == 0.5
//
//    timeval3.it_interval.tv_sec = 0;
//    timeval3.it_interval.tv_usec = 500000;// == 0.5
#endif
    
    setitimer(ITIMER_REAL, &timeval, &oldTimeval);//系统真实时间 SIGALRM //最后一个可以空
//    setitimer(ITIMER_VIRTUAL, &timeval2, &oldTimeval2);//用户态时间 SIGVTALRM 进程执行时间 linux 中可以
//    setitimer(ITIMER_PROF, &timeval3, NULL);//用户态/内核态下时间 SIGPROF//对进程 P1 来说从 5 点 10 分开始的 1 分钟内，虽然自己的执行时间为 30 秒，但实际上还有 10 秒钟内核是在执行 P1 发起的系统调用，那么这 10 秒钟也被加入到 PROF 时间。这种时间定义主要用于全面衡量进程的性能 linux 中可以
    
}

//}
//__END_DECLS

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    signal(SIGALRM, [](int t) {
        std::cout << "sigalrm: " << t << std::endl;
    });
    
    signal(SIGVTALRM, [](int t) {
        std::cout << "sigvtalrm: " << t << std::endl;
    });
    
    signal(SIGPROF, [](int t) {
        std::cout << "sigprof: " << t << std::endl;
    });
    
    start_timer_test();
    
    while (true) {
        std::cout << "please input: " << std::endl;
        
        int tag;
        std::cin >> tag;

        if (tag >= 10) {
            int t = tag / 10;
            auto il = alarm(t);
            std::cout << "al: " << il << std::endl;
        }
    }
    
    return 0;
}
