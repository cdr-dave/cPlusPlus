//
//  main.cpp
//  qt 信号与槽
//
//  Created by cdr on 2022/5/15.
//

#include <iostream>
#include "QObject.hpp"

void connect(void* source, const char* sigName, void* desc, const char* sloName) {
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    QObject obj;
    obj.mainFunc();
    obj.moc_callfunc();
    return 0;
}
