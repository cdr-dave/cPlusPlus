//
//  main.cpp
//  debug_new
//
//  Created by cdr on 2022/5/31.
//

#include <iostream>
#include "debug_new.h""

void call_1() {
    int* tip = new int(32);
}
void call_0() {
    call_1();
    
    double* dd = new double(2.0);
    delete dd;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    {
        call_0();
    }
    
    return 0;
}
