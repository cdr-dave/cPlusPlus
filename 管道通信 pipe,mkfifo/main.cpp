//
//  main.cpp
//  管道通信 pipe/mkfifo
//
//  Created by cdr on 2022/7/18.
//

/*
 1. 父子/兄弟进程
 2. 半双工，数据只能一端到一端，双方通信需要两个管道  只要有一端关闭，另外一端就读取不到数据，虽然依旧可以read,但是之前write没有了，且不会阻塞了
 3. 队列读写，写在队尾，读从对头弹出
 4. 独立文件系统，存在与内存中 生成文件描述符，使用文件实现数据流动
 
 */
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
#include <stdio.h>
#include <signal.h>

#include "Lambda_2_ptr.h"
#include <list>

#define test_pipe 1

//class Data {
//public:
//    void operator ()(int i) {
//        std::cout << "data () " << std::endl;
//        closeTag = true;
//    }
//
//    void c_call(int i) {
//        std::cout << "data () " << std::endl;
//        closeTag = true;
//    }
//
//
//    bool closeTag = false;
//};

void read_func(int read_p, bool isParent) {
    std::string name = isParent ? "parent" : "child";
    
    std::cout << name << " start read !!!" << std::endl;
    
    char data[100];
    
//    sleep(5);
//    Data dd;
    bool closeW = false;
    auto call_lam = [&](int) {
        printf("============================");
        closeW = true;
    };
//    dd(32);
//    signal(SIGUSR1, dd);
//    void (*call)(int) = nullptr;
//    std::function<void(int)> func = dd;
    
    void (*call)(int) = Lambda_2_ptr::ptr<int>(call_lam);
    
    signal(SIGUSR1, call);
//    struct sigaction sa;
//    sa.sa_flags = SIGUSR1;
//    sigemptyset(&sa.sa_mask);
//    sa.sa_sigaction = [](int sig, siginfo_t *info, void *ctx) {
//
//    };;
    
//    sigaction(SIGUSR1, &sa, NULL);
    
    while (true) {
        memset(data, 0, sizeof(data));
        size_t ret = read(read_p, data, sizeof(data));
        
        printf("%s: read data -> %s, code -> %ld\n", name.c_str(), data, ret);
        
        if (closeW) {
            printf("close wwwwww\n");
            break;
        }
    }
    
    std::cout << name << " end read !!!" << std::endl;
    
}

void write_func(int write_p, bool isParent) {
    std::string name = isParent ? "parent" : "child";
    
    std::cout << name << " start write !!!" << std::endl;
    
    int i = 0;
    while (true) {
        if (i > 2) break;;
        
        sleep(2);
        
        std::string send = name + std::string(" , tag ") + std::to_string(i);
        printf("%s start send!!\n", name.c_str());
        
        write(write_p, send.c_str(), send.length() + 1);//写入
        
        i++;
        
    }
    
    
    std::cout << name << " end write !!!" << getppid() << std::endl;
    
    sleep(10);
    
//    raise(SIGUSR1);
//    kill(0, SIGUSR1);
    kill(getppid(), SIGHUP);
    
//    union sigval sv;
//    sv.sival_int = 320;
//    sv.sival_ptr
    
//    sigqueue(pid, SIGUSR1, sv);
    
    //不会触发
    printf("end thread !!!\n");
    
}

void startThread(bool isParent, int id[]) {
    if (isParent) {
        std::thread th_read(read_func, id[0], isParent);
        th_read.detach();
    }
    else
    {
        std::thread th_write(write_func, id[1], isParent);
        th_write.detach();
        
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int file_descriptor[2];
    int ret = pipe(file_descriptor);
    if (ret < 0) {
        perror("pipe err!!!");
        return 1;
    }
    
    pid_t id = fork();
    if (id < 0) {
        std::cout << "fork error !" << std::endl;
        return 2;
    }
    
    if (id == 0) //child
    {
        close(file_descriptor[0]);//关掉读
        std::cout << "child proc id: " << getpid() << ",ppid "<< getppid() << std::endl;
        
        startThread(false, file_descriptor);
        
//        pause();
        
        //后面的不会调用到
        std::cout << "child end pause !!!" << std::endl;
        
//        sleep(20);
        
        std::cout << "child end proc !!!" << std::endl;
        
    }
    else //parent
    {
        close(file_descriptor[1]);//关掉写
        std::cout << "parent proc id: " << getpid() << ", child " << id << ",ppid "<< getppid() << std::endl;
        
        startThread(true, file_descriptor);
        
        
//        wait(NULL); //等待子进程结束
        std::cout << "parent end wait !!!" << std::endl;
        
        sleep(25);
        std::cout << "parent end proc !!!" << std::endl;
    }
    
    return 0;
}
