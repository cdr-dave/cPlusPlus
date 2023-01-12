//
//  main.cpp
//  c20Ranges
//
//  Created by cdr on 2022/5/25.
//

#include <iostream>
#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <experimental/algorithm>
//#include <experimental/iterator>
#include <ranges>>

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    using namespace std::experimental::ranges;
    int a[] = {34, 3, 33, 1, 22, 77};
    copy(a, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    return 0;
}
