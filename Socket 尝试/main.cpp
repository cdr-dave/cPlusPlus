//
//  main.cpp
//  Socket 尝试
//
//  Created by cdr on 2022/6/24.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <iostream>
#include <netinet/tcp.h>

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8099);
//    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
     serv_addr.sin_addr.s_addr = inet_addr("116.205.177.214");
    TCP_FASTOPEN;
    int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof serv_addr);
    if (ret == -1) { std::cerr << "connect error.\n"; exit(-1); }

    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        std::cin >> buffer;

        ret = send(sock, buffer, strlen(buffer), 0);
        if (ret == -1) { std::cerr << "send error.\n"; exit(-1); }
        else if (ret == 0) { std::cerr << "peer closed.\n"; exit(-1); }
    }

    return 0;
}

