//
//  main.cpp
//  向量强异常安全性
//
//  Created by cdr on 2022/5/3.
//

#include <iostream>
#include <vector>

using namespace std;

class Obj1 {
public:
  Obj1()
  {
    cout << "Obj1()\n";
  }
  Obj1(const Obj1&)
  {
    cout << "Obj1(const Obj1&)\n";
  }
//  Obj1(Obj1&&)
//  {
//    cout << "Obj1(Obj1&&)\n";
//  }
};
class Obj2 {
public:
  Obj2()
  {
    cout << "Obj2()\n";
  }
  Obj2(const Obj2&)
  {
    cout << "Obj2(const Obj2&)\n";
  }
  Obj2(Obj2&&) noexcept
  {
    cout << "Obj2(Obj2&&)\n";
  }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<Obj1> v1;
    v1.reserve(2);
    v1.emplace_back();
    v1.emplace_back();
//    v1.push_back(Obj1());
    v1.emplace_back();
    vector<Obj2> v2;
    v2.reserve(2);
    v2.emplace_back();
    v2.emplace_back();
//    v2.push_back(Obj2());
    v2.emplace_back();
//    v2.push_back(Obj2());
    /*
     
     Obj1()
     Obj1()
     Obj1()
     Obj1(const Obj1&)
     Obj1(const Obj1&)
     Obj2()
     Obj2()
     Obj2()
     Obj2(Obj2&&)
     Obj2(Obj2&&)
     //如果其中 v2.emplace_back() 修改为 v2.push_back(Obj2());//会多一次 Obj2(Obj2&&)，这个多出来的是构造的时候，不是扩容的时候 ？？明明是2的容器的小变成3，扩容的时候怎么是移动两次？
     
     vector 通常保证强异常安全性，如果元素类型没有提供一个保证不抛异常的移动构造函数，vector 通常会使用拷贝构造函数。因此，对于拷贝代价较高的自定义元素类型，我们应当定义移动构造函数，
     并标其为 noexcept，或只在容器中放置对象的智能指针。
     
     尝试：
     vector<Obj2> v2;
     v2.reserve(1);
     v2.emplace_back();
     v2.emplace_back();
     
     v2.reserve(2);
     v2.emplace_back();
     
     Obj2()
     Obj2()
     Obj2(Obj2&&)
     Obj2()
     Obj2(Obj2&&)
     Obj2(Obj2&&)
     
     结果移动次数同reserve 大小
     原因：
     查看 reverse
     vector<_Tp, _Allocator>::reserve(size_type __n)
     {
         if (__n > capacity())
         {
             allocator_type& __a = this->__alloc();
             __split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
             __swap_out_circular_buffer(__v);
         }
     }
     
     回顾emplace_back 越界情况下
     __emplace_back_slow_path：
     
     allocator_type& __a = this->__alloc();
     __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
 //    __v.emplace_back(_VSTD::forward<_Args>(__args)...);
     __alloc_traits::construct(__a, _VSTD::__to_address(__v.__end_), _VSTD::forward<_Args>(__args)...);
     __v.__end_++;
     __swap_out_circular_buffer(__v);
     
     其中： construct 是构建产生越界时那次的对象构造，查看前面，__alloc/__split_buffer 调用了 reverse操作
     也就是因此，可以知道，当我们产生插入的操作的时候，是先重构大小，接着才 调用插入的，也就是，为什么移动次数没算上产生重构那次操作（包括 push_back）
     
     如果其中 v2.emplace_back() 修改为 v2.push_back(Obj2());//会多一次 Obj2(Obj2&&)
     这是因为，emplace_back 源码如下，
     vector<_Tp, _Allocator>::emplace_back(_Args&&... __args)
     {
         if (this->__end_ < this->__end_cap())
         {
             __construct_one_at_end(_VSTD::forward<_Args>(__args)...);//这个是容器大小刚好前构建对象
         }
         else
             __emplace_back_slow_path(_VSTD::forward<_Args>(__args)...);//这个是越界的时候构建的
     #if _LIBCPP_STD_VER > 14
         return this->back();
     #endif
     }
     
     
     最终在 构造前调用的是 allocator.h的
     void construct(_Up* __p, _Args&&... __args) {
         ::new ((void*)__p) _Up(_VSTD::forward<_Args>(__args)...);
     是不是熟悉，（new placement obj())
     
     首先我们知道 vector 有个 size/capacity 概念 即：元素数量和存储大小区别，也就是vector 回预加载一定数量内存（大于实际大小），
     此时 搭配上 new placement obj(), 指定内存块构建对象
     
     也就是实现了，直接在vector内存上直接构建，而不用移动的操作，反过来看
     push_back(obj())//跟踪发现，obj() 首先调用，接着下面Push_back
     vector<_Tp, _Allocator>::push_back(value_type&& __x)
     {
         if (this->__end_ < this->__end_cap())
         {
             __construct_one_at_end(_VSTD::move(__x));//这个是容器大小刚好前构建对象 这里发生了移动，也就是多一次移动的原因，实际上，虽然构造看似一样调用了，其实内在调用者确实不一样的，emplace_back 的是容器去调用对象的构造
         }
         else
             __push_back_slow_path(_VSTD::move(__x));
     }
     
     
     
     */
    return 0;
}
