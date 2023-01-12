//
//  main.cpp
//  Http服务器
//
//  Created by cdr on 2022/5/10.
//

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <signal.h>
#include <string>
#include <fstream>

#define ERR_EXIT(m) \
    do { std::cerr << m << std::endl; close(EXIT_FAILURE); } while(0)

typedef struct sockaddr SA;

int main(int argc, const char * argv[]) {
    signal(SIGCHLD, SIG_IGN);//信号处理，避免子程序僵尸
    int listenfd, connfd, pid;
    socklen_t addLen;
    struct sockaddr_in clientAdd, serveAdd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        ERR_EXIT("socket");
    }
    
    int flag = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    //SO_REUSEADDR BOOL 允许套接口喝一个已在使用中的地址绑定
    //SOL_SOCKET 固定level 设置
    bzero(&serveAdd, sizeof(serveAdd));//清空
    serveAdd.sin_family = AF_INET;//协议家族
    serveAdd.sin_port = htons(8080);//默认80
    serveAdd.sin_addr.s_addr = htonl(INADDR_ANY);
    //INADDANY == 0 作用适配地址
    if (bind(listenfd, (SA*)&serveAdd, sizeof(serveAdd)) == 1) {
        ERR_EXIT("bind");
    }
    
    //3 等待队列。syn 队列长度
    if (listen(listenfd, 3) == 1) {
        ERR_EXIT("listen");
    }
    
    while (1) {
        if ((connfd = accept(listenfd, (SA*)&clientAdd, &addLen)) == 1) {
            ERR_EXIT("accept");
        }
        pid = fork();//fork 出来子进程
        if (pid) {
            close(connfd);
            //父进程关闭connfd 然后仅仅进行 listen. SINGCHLD 自动收尸
        }
        else
        {
            close(listenfd);//子进程进行发送响应报文
            char buffer[1024];
            
            recv(connfd, buffer, sizeof(buffer), 0);
            
            std::cout << "##########################http request begin####################" << std::endl;
            //打印recv 的来自客户端的请求并且输出请求信息
            std::cout << buffer << std::endl;
            std::cout << "##########################http request end #####################" << std::endl;
            
            std::ifstream ifs("./index.html");
            if (ifs) {
                size_t len = -1;
                ifs.seekg(0L, ifs.end);//定位到末尾
                len = ifs.tellg();//获取文件长度
                ifs.seekg(0L, ifs.beg);//回到文件开头
                
                char* file = new char[len];
                ifs.read(file, len);//读取正文，字符串形式读取
                ifs.close();
                
                //开始处理响应
                std::string black = "\r\n";
                std::string status_line = "HTTP/1.1 200 OK\r\n";//状态行=>版本 状态 短语CRLF
                std::string reply_header;//响应头部
                reply_header += "Content-Length: " + std::to_string(len) + black;
                
                send(connfd, status_line.c_str(), status_line.size(), 0);//状态行
                send(connfd, reply_header.c_str(), reply_header.size(), 0);//响应头部
                send(connfd, black.c_str(), black.size(), 0);//CRLF 空行
                send(connfd, file, len, 0);//响应正文
                
                delete []file;
            }
            
            close(connfd);
            exit(EXIT_SUCCESS);
        }
    }
    
    close(listenfd);
    
    return 0;
}
