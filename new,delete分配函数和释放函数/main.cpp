//
//  main.cpp
//  new/delete分配函数和释放函数
//
//  Created by cdr on 2022/5/31.
//

#include <iostream>
#include <stdio.h>

void* operator new(size_t size, int tag) {
//    std::cout << "__CUSTOM_NEW_FUNC__" << std::endl;
    printf("__CUSTOM_NEW_FUNC__\n");
    void* ptr = malloc(size);
    if (ptr == nullptr) {
        throw std::bad_alloc();
    }
    
    return ptr;
}

void operator delete(void* ptr) noexcept
{
//    std::cout << "__CUSTOM_DELETE_FUNC__" << std::endl;
    printf("__CUSTOM_DELETE_FUNC__\n");
    free(ptr);
}

void* operator new[](size_t size)
{
    return operator new(size);
}

void operator delete[](void* ptr) noexcept
{
    operator delete(ptr);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::cout << "Hello, World!\n";
    int* iptr = new(32) int(11);
//    std::cout << "new data is: " << *iptr << std::endl;
    delete iptr;
    
    
    return 0;
}
