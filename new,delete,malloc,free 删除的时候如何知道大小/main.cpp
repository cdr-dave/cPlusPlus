//
//  main.cpp
//  new/delete/malloc/free 删除的时候如何知道大小
//
//  Created by cdr on 2022/6/1.
//

#include <iostream>
#include <vector>
#include <thread>

#define TEST_NUM_TYPE unsigned//unsigned long long
using namespace std;
struct Obj_Data {
    int iNum = 21;
    double dNum = 11.22;
    char ch = 'a';
};

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
//    {
//        size_t aSize = sizeof(TEST_NUM_TYPE) * 3;
//        void* vptr = malloc(aSize);
//        auto iptr = (int*)vptr;//new TEST_NUM_TYPE[3];
////        *iptr = 9;
//        iptr[0] = 5;
//        iptr[1] = 7;
//        iptr[2] = ~0;
//
//        auto pp = iptr - 3;
//        auto pp2 = iptr + 2;
////        delete iptr;
//        free(vptr);
//    }
    
//    this_thread::sleep_for(4s);
    {
        void* d1 = malloc(1);
        memset(d1, 1, 1);
        void* d2 = malloc(2);
        memset(d2, 1, 2);
        void* d3 = malloc(3);
        memset(d3, 1, 3);
        void* d4 = malloc(4);
        memset(d4, 1, 4);
        void* d5 = malloc(5);
        memset(d5, 1, 5);
        void* d6 = malloc(6);
        memset(d6, 1, 6);
        void* d7 = malloc(7);
        memset(d7, 1, 7);
        void* d8 = malloc(8);
        memset(d8, 1, 8);
        void* d9 = malloc(9);
        memset(d9, 1, 9);
        
        vector<char*> arr;
        vector<char*> arr2;
         auto dp2 =reinterpret_cast<char*>(d2) - 16;
        auto dp3 =reinterpret_cast<char*>(d3) - 16;
        auto dp4 =reinterpret_cast<char*>(d4) - 16;
        auto dp9 =reinterpret_cast<char*>(d9) - 16;
        auto dp92 =reinterpret_cast<char*>(d9) - 2;
        auto dp93 =reinterpret_cast<char*>(d9) - 3;
//        for (int i = 0; i < 20; i++) {
//
//             auto dpp =reinterpret_cast<char*>(d2) - i;
//            arr.push_back(dpp);
//        }
//
//        for (int i = 0; i < 20; i++) {
//
//             auto dpp =reinterpret_cast<char*>(d2) + 1;
//            arr.push_back(dpp);
//        }
//
//        for (int i = 0; i < 20; i++) {
//
//             auto dpp =reinterpret_cast<char*>(d3) - i;
//            arr2.push_back(dpp);
//        }
//
//        for (int i = 0; i < 20; i++) {
//
//             auto dpp =reinterpret_cast<char*>(d3) + 1;
//            arr2.push_back(dpp);
//        }
//        memset(dd, 1, 1);
        unsigned in = ~0 - 2;
        unsigned ii = 1;
        cout << in << endl;
    }
    {
        
        size_t aSize = sizeof(TEST_NUM_TYPE);
        size_t objSize = sizeof(Obj_Data);
        void* vptr = malloc(aSize + objSize);
        auto optr = reinterpret_cast<Obj_Data*>(vptr);
        optr->iNum = 3;
        optr->dNum = 13.3;
        optr->ch = '3';
        auto icptr = reinterpret_cast<char*>(vptr) + objSize;
        auto iptr = reinterpret_cast<TEST_NUM_TYPE*>(icptr);
        *iptr = 9;
        *iptr = ~0;
        free(iptr);
        free(vptr);
    }
    cout << "test end!!!" << endl;
    return 0;
}
