//
//  main.cpp
//  函数对象的容器
//
//  Created by cdr on 2022/5/5.
//


#include <algorithm>   // std::sort
#include <functional>  // std::less/greater/hash
#include <iostream>    // std::cout/endl
#include <string>      // std::string
#include <vector>      // std::vector
#include <queue> // std::priority_queue
#include <map>
//#include "output_container.h"

#include <tuple>

using namespace std;

using namespace std;

template<class T>
struct less : std::binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const {
        return x < y;
    }
};


int main()
{
  // 初始数组
  vector<int> v{13, 6, 4, 11, 29};
//  cout << v << endl;

  // 从小到大排序
  sort(v.begin(), v.end());
//  cout << v << endl;

  // 从大到小排序
  sort(v.begin(), v.end(),
       greater<int>());
//  cout << v << endl;

  cout << hex;

  auto hp = hash<int*>();
  cout << "hash(nullptr)  = "
       << hp(nullptr) << endl;
  cout << "hash(v.data()) = "
       << hp(v.data()) << endl;
  cout << "v.data()       = "
       << static_cast<void*>(v.data())
       << endl;

  auto hs = hash<string>();
  cout << "hash(\"hello\")  = "
       << hs(string("hello")) << endl;
  cout << "hash(\"hellp\")  = "
       << hs(string("hellp")) << endl;
    
    priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>> q;
    q.push({1, 1});
    q.push({2, 2});
    q.push({0, 3});
    q.push({9, 4});
    
    while (!q.empty()) {
        auto cc = q.top();
        cout << cc.first << "," << cc.second << endl;
        q.pop();
        
    }
    
    

    multimap<string, int> mmp{
      {"one", 1},
      {"two", 2},
      {"three", 3},
      {"four", 4},
        {"four", 5},
        {"four", 0},
    };
    
    multimap<string, int>::iterator lower, upper;
    std::tie(lower, upper) = mmp.equal_range("four");
    
//    if (lower != upper) printf("...");
    for (auto iter = lower; iter != upper; iter++) {
        cout << iter->second << endl;
    }
}
