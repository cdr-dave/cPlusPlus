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
#include <stdio.h>
//#include <sys/sigqueue.h>
/*
 
 Hello, World!
 139908691203904
 parent start 139908691203904
 child start 139908691203904
 child end
 parent end
 recv a sig = 13 data = 320 data = 320
 child resume
 */

//linux 中可以

#define SIG_TAG 13 //SIGUSR1 //本质上，只要不是设置 signal(id, handler) handler 1/3 都是一样自己处理的 除了 SIGSTOP/ SIGKILL
/*
 handler：
 SIG_IGN --> 1. 不响应该信号，忽略该信号
 fun --> 2. 处理函数：void (*sighandler_t)(int); 我想去做什么就写在这个函数中
 SIG_DFL --> 3. 默认动作
 */

using namespace std;
void sig_call(int sig, siginfo_t *info, void *ctx)
{
    printf("recv a sig = %d data = %d data = %d\n", sig, info->si_value.sival_int, info->si_value.sival_int);
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
        
        union sigval sv;
        sv.sival_int = 320;
        
        sigqueue(x, SIG_TAG, sv);//Linux中可以
//        kill(x, SIG_TAG);
//        kill(x, SIGRTMIN);
        
        wait(NULL);
        
    }
    
    //child; //子进程捕捉信号
    if (x == 0) {
        //提前捕捉SIGUSR1这个信号，将来子进程收到这个信号，则
                //运行signal_fun这个函数
        std::cout << "child start " << std::this_thread::get_id() << std::endl;
//        signal(SIG_TAG, sig_call);
        struct sigaction saction;
        saction.sa_sigaction = sig_call;
        sigemptyset(&saction.sa_mask);
        saction.sa_flags = SA_SIGINFO;
        if (sigaction(SIG_TAG, &saction, NULL) < 0) {
            perror("s action err");
            exit(0);
        }
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
