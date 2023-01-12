//
//  main.cpp
//  fork 学习
//
//  Created by cdr on 2022/7/19.
//

#include <iostream>
#include <unistd.h>

#define FILE_NNAME "file_point"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    char sh[100] = "first data test";
    char* nh = new char[100]();
    std::string str = "first string";
    int * ni = new int(32);
    
    FILE* fp = fopen(FILE_NNAME, "a+");
    if (fp == NULL) {
        std::cout << "fopen failed." << std::endl;
        return 1;
    }
    
    std::cout << "start fork " << std::endl;
    
    int x = fork();
    
    if (x < 0) {
        std::cerr << "fork error !!!" << std::endl;
    }
    
    if (x == 0) {
        double* f_d = new double(2);
        
        sleep(5);
        
        std::cout << "child pro !!! " << getpid() << " parent id: " << getppid() << std::endl;

        std::cout << "address: " << static_cast<void*>(sh) << ", " << static_cast<void*>(nh) << std::endl;
        std::cout << "double address: " << static_cast<void*>(f_d) << std::endl;

        std::cout << "sh: " << sh << std::endl
        << "nh: " << nh << std::endl
        << "str: " << str << std::endl
        << "ni: " << *ni << std::endl;

        fseek(fp, 0, SEEK_SET);
        char buf[100] = { 0 };
        size_t ret = fread(buf, 1, strlen(sh), fp);
        if (ret < 0) {
            std::cerr << "fread failed !!" << std::endl;
            return 1;
        }
        else if (ret == 0) {
            if (feof(fp)) {
                std::cout << "end the file" << std::endl;
//                return 0;
            }
            else
            {
                std::cerr << "fread error: ret is zero" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "parent buf: " << buf << std::endl;
        }

        fclose(fp);

        std::cout << "end child data!!" << std::endl;
        
        
    }
    else
    {
        double* f_d = new double(2);//跟child 地址不一样
        std::string temp = "parent data tst";
        strcpy(sh, temp.c_str());
        
        temp = "parent new data tst";
        strcpy(nh, temp.c_str());
        
        *ni = 111111;
        str = "parent string";
        
        fwrite(sh, 1, strlen(sh), fp);
        
        std::cout << "parent address: " << static_cast<void*>(sh) << ", " << static_cast<void*>(nh) << std::endl;//跟child 的地址一样
        std::cout << "double address: " << static_cast<void*>(f_d) << std::endl;
        
        std::cout << "sh: " << sh << std::endl
        << "nh: " << nh << std::endl
        << "str: " << str << std::endl
        << "ni: " << *ni << std::endl;
        
        fseek(fp, 0, SEEK_SET);
        char buf[100] = { 0 };
        size_t ret = fread(buf, 1, strlen(sh) + 1, fp);
        if (ret < 0) {
            std::cerr << "fread failed !!" << std::endl;
            return 1;
        }
        else if (ret == 0) {
            if (feof(fp)) {
                std::cout << "end the file" << std::endl;
//                return 0;
            }
            else
            {
                std::cerr << "fread error: ret is zero" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "parent buf: " << buf << std::endl;
        }
        
        std::cout << "end parent data!!" << std::endl << std::endl << std::endl;
        
//        wait(NULL);
    }

    
    return 0;
}

/*
 虽然共享了虚拟内存地址，实际上，堆栈空间是各自的
 不过文件句柄是共享的，可以进行操作，类似的，其实 pipe( 通道也是可以共享的
 
 Hello, World!
 start fork
 parent address: 0x7ff7bfeff220, 0x1007171c0
 double address: 0x10140f5a0
 sh: parent data tst
 nh: parent new data tst
 str: parent string
 ni: 111111
 end parent data!!


 child pro !!! 30531 parent id: 30518
 address: 0x7ff7bfeff220, 0x1007171c0
 double address: 0x101212d30
 sh: first data test
 nh:
 str: first string
 ni: 32
 end child data!!
 
 */
