//
//  main.cpp
//  多线程
//
//  Created by cdr on 2022/5/22.
//

#include <iostream>
#include <thread>
#include <future>

namespace std {

int threadCall(int n) {
    std::this_thread::sleep_for(5000ms);
    return n + 1;
}

void refTestWork(std::condition_variable& cv, int& ret) {
    this_thread::sleep_for(2s);
    ret = 100;
    cv.notify_one();
}

}

int x, y;
void automicTest() {
    x = 1;
    y = 2;
}

void automicTest2() {
    if (y == 2){
        x = 11;
        y = 20;
    }
}

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    
    int index = 10;
    while (index > 0) {
        thread th_1(automicTest), th_2(automicTest2);
        th_1.detach();
        th_2.detach();
        std::this_thread::sleep_for(20ms);
        cout << x << ", " << y << endl;
        std::this_thread::sleep_for(30ms);
        index--;
    }
   
    int cn;
    auto f = [&]() { cn++; };
    std::thread t1(f), t2(f), t3(f);
    t1.detach();
    t2.detach();
    t3.detach();
    //普通使用 std::ref 传递应用获取异步结果
    std::condition_variable cv;
    std::mutex cv_mutex;
    int ret = 0;
    std::thread th(std::refTestWork, std::ref(cv), std::ref(ret));
    th.detach();
    std::cout << "thread ref test start: " << ret << std::endl;
    std::unique_lock cv_lock {cv_mutex};
    cv.wait(cv_lock);
    std::cout << "thread ref end: ret is : " << ret << std::endl;
//    std::lock_guard<std::mutex> cv_lock(cv_mutex);
    
    //async 获取异步结果
    auto fn = std::async(std::launch::async, std::threadCall, 32);
    std::cout << "async main start:" << std::endl;
    std::cout << "async ret: " << fn.get() << std::endl;
    std::cout << "async main end:" << std::endl;
    
    std::cout << std::numeric_limits<unsigned char>::digits << std::endl;
    std::cout << std::numeric_limits<unsigned>::digits << std::endl;
    
    std::cout << cn << std::endl;
    
    return 0;
}

