//
//  main.cpp
//  信号 kill
//
//  Created by cdr on 2022/7/17.
//

#include <iostream>
#include <signal.h>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>

/*
 
 Hello, World!
 0x100098600
 parent start 0x100098600
 child start 0x100098600
 child end
 <<sleep>>
 parent end //有可能在最后一行
 sig call 30, id 0x100098600
 child resume
 */

//有趣的是 linux 中 kill -l  可以知道，信号 有
/*
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
  6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
 11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
 16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
 21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
 26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
 31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
 38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
 43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
 48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
 53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
 58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
 63) SIGRTMAX-1  64) SIGRTMAX
 */
//macOS 中没有这个，而且，测试结果 SIG_TAG == 64 也是失败的

// #define SIGHUP  1       /* hangup */
// #define SIGINT  2       /* interrupt */
// #define SIGQUIT 3       /* quit */
// #define SIGILL  4       /* illegal instruction (not reset when caught) */
// #define SIGTRAP 5       /* trace trap (not reset when caught) */
// #define SIGABRT 6       /* abort() */
// #if  (defined(_POSIX_C_SOURCE) && !defined(_DARWIN_C_SOURCE))
// #define SIGPOLL 7       /* pollable event ([XSR] generated, not supported) */
// #else   /* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
// #define SIGIOT  SIGABRT /* compatibility */
// #define SIGEMT  7       /* EMT instruction */
// #endif  /* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
// #define SIGFPE  8       /* floating point exception */
// #define SIGKILL 9       /* kill (cannot be caught or ignored) */
// #define SIGBUS  10      /* bus error */
// #define SIGSEGV 11      /* segmentation violation */
// #define SIGSYS  12      /* bad argument to system call */
// #define SIGPIPE 13      /* write on a pipe with no one to read it */
// #define SIGALRM 14      /* alarm clock */
// #define SIGTERM 15      /* software termination signal from kill */
// #define SIGURG  16      /* urgent condition on IO channel */
// #define SIGSTOP 17      /* sendable stop signal not from tty */
// #define SIGTSTP 18      /* stop signal from tty */
// #define SIGCONT 19      /* continue a stopped process */
// #define SIGCHLD 20      /* to parent on child stop or exit */
// #define SIGTTIN 21      /* to readers pgrp upon background tty read */
// #define SIGTTOU 22      /* like TTIN for output if (tp->t_local&LTOSTOP) */
// #if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
// #define SIGIO   23      /* input/output possible signal */
// #endif
// #define SIGXCPU 24      /* exceeded CPU time limit */
// #define SIGXFSZ 25      /* exceeded file size limit */
// #define SIGVTALRM 26    /* virtual time alarm */
// #define SIGPROF 27      /* profiling time alarm */
// #if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
// #define SIGWINCH 28     /* window size changes */
// #define SIGINFO 29      /* information request */
// #endif
// #define SIGUSR1 30      /* user defined signal 1 */
// #define SIGUSR2 31      /* user defined signal 2 */
 

#define SIG_TAG SIGXCPU //SIGUSR1 //本质上，只要不是设置 signal(id, handler) handler 1/3 都是一样自己处理的 除了 SIGSTOP/ SIGKILL
/*
 handler：
 SIG_IGN --> 1. 不响应该信号，忽略该信号
 fun --> 2. 处理函数：void (*sighandler_t)(int); 我想去做什么就写在这个函数中
 SIG_DFL --> 3. 默认动作
 */

using namespace std;
void sig_call(int n) {
    std::cout << "sig call " << n << ", id " << std::this_thread::get_id() << std::endl;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n" << std::this_thread::get_id() << std::endl;
    pid_t x;
    
    x = fork();
    
    //is parent
    if (x > 0) {//父进程发送信号
        std::cout << "parent start " << std::this_thread::get_id() << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(2)); //确保子进程signal()先运行
        
        std::cout << "parent end \n";
        
        kill(x, SIG_TAG);
//        kill(x, SIGRTMIN);
        
        wait(NULL);
        
    }
    
    //child; //子进程捕捉信号
    if (x == 0) {
        //提前捕捉SIGUSR1这个信号，将来子进程收到这个信号，则
                //运行signal_fun这个函数
        std::cout << "child start " << std::this_thread::get_id() << std::endl;
        signal(SIG_TAG, sig_call);
        std::cout << "child end" << std::endl;
        
        pause(); //等待信号到来
        /*
         功能：  pause - wait for signal

           收到信号  --> pause返回
           没有收到信号  --> pause阻塞，直到收到信号为止
         */
        
        std::cout << "child resume " << std::endl;
    }
    
    return 0;
}
