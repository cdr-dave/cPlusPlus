//
//  main.cpp
//  容器分配器
//
//  Created by cdr on 2022/6/2.
//

#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>

//using namespace std;

template<class T>
struct Mallocator
{
    /*
     给定
     T ，无 cv 限定的对象类型
     A ， T 类型的分配器 (Allocator) 类型
     a ， A 类型对象
     B ，某无 cv 限定的对象类型 U 的对应分配器 (Allocator) 类型（由重绑定 A 获得）
     b ， B 类型对象
     p ， allocator_traits<A>::pointer 类型值，由调用 allocator_traits<A>::allocate() 获得
     cp ， allocator_traits<A>::const_pointer 类型值，由从 p 转换获得
     vp ， allocator_traits<A>::void_pointer 类型值，由从 p 转换获得
     cvp ， allocator_traits<A>::const_void_pointer 类型值，由从 cp 或从 vp 转换获得
     xp ，指向某无 cv 限定类型 X 的可解引用的指针
     r ，由表达式 *p 获得的 T 类型左值
     n ， allocator_traits<A>::size_type 类型值
     
    allocator__traits.h
     
     using allocator_type = _Alloc;
     using value_type = typename allocator_type::value_type;
     using pointer = typename __pointer<value_type, allocator_type>::type;
     using const_pointer = typename __const_pointer<value_type, pointer, allocator_type>::type;
     using void_pointer = typename __void_pointer<pointer, allocator_type>::type;
     using const_void_pointer = typename __const_void_pointer<pointer, allocator_type>::type;
     using difference_type = typename __alloc_traits_difference_type<allocator_type, pointer>::type;
     using size_type = typename __size_type<allocator_type, difference_type>::type;
     using propagate_on_container_copy_assignment = typename __propagate_on_container_copy_assignment<allocator_type>::type;
     using propagate_on_container_move_assignment = typename __propagate_on_container_move_assignment<allocator_type>::type;
     using propagate_on_container_swap = typename __propagate_on_container_swap<allocator_type>::type;
     using is_always_equal = typename __is_always_equal<allocator_type>::type;
     */
    typedef T value_type;//没有的话 No type named 'value_type' in 'Mallocator<int>' allocator__traits.h中用到
    
    Mallocator() = default; //delete的话 了 call to deleted constructor of 'Mallocator<int>'
//    template<class U> constexpr Mallocator(const Mallocator<U>&) noexcept {//虽然一般是与 T 的抑制，但是，这里指代的是模版中的，不是返回的T（
////        std::cout << typeid(Mallocator<U>::size_type).name() << std::endl;
//    }
    
    [[nodiscard]] T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_array_new_length();
        }
        
//        std::cout << typeid(__size_type<Mallocator, difference_type>::type).name() << std::endl;
        
        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            report(p, n);
            return p;
        }
        
        throw std::bad_alloc();
    }
    
    void deallocate(T* p, std::size_t n) noexcept {
        report(p, n, 0);
        std::free(p);
    }
    
private:
    void report(T* p, std::size_t n, bool alloc = true) const {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
        << " bytes at " << std::hex << std::showbase
        << reinterpret_cast<void*>(p) << std::dec << std::endl;
    }
};

template <class T, class U>
bool operator==(const Mallocator<T>&, const Mallocator<U>&) {
    return true;
}

template<class T, class U>
bool operator!=(const Mallocator<T>&, const Mallocator<U>&) {
    return false;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    vector<int> arr;
//    arr.push_back(232);
//    arr.push_back(11);
//    arr.push_back(3);
    std::vector<int, Mallocator<int>> v(2);//有趣的概念，未优化时，不管大小多大，设置了大小，第一次 push 依旧会重新分配大小（2倍），然后push 超过大小，就会重新分配（每次都是2倍，除了申请空间开销，本事内存你只是调用了移动，没啥开销）
    v.push_back(42);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    v.push_back(11);
    return 0;
}
