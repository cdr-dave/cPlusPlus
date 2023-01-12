//
//  FockTest.cpp
//  Http服务器
//
//  Created by cdr on 2022/5/10.
//

//#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <thread>

int main() {
    int i = 1;
    if (!fork()) i++;
//    printf("%d, %d\n", i, std::this_thread::get_id());
//    std::cout << i << std::endl;
    
    if (!fork()) i++;
//    std::cout << i << std::endl;
//    printf("%d, %d\n", i, std::this_thread::get_id());
    
    return 0;
}

