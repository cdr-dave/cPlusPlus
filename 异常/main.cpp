//
//  main.cpp
//  异常
//
//  Created by cdr on 2022/5/6.
//

#include <iostream>

using namespace std;
void excuteException(int ie)  {
    if (ie == 11) {
        throw std::runtime_error("exuteException err");
    }
    
    cout << "success excute exc, " << ie << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    try {
        excuteException(2);
        excuteException(11);
        excuteException(22);
    } catch (exception e) {
        cout << e.what() << endl;
    }
    
    
    return 0;
}
