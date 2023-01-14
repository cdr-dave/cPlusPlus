//
//  Lambda_2_ptr.hpp
//  Lambda_2_ptr
//
//  Created by cdr on 2022/7/25.
//

#ifndef Lambda_2_ptr_
#define Lambda_2_ptr_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <iostream>
#include <type_traits>

class Lambda_2_ptr
{
public:
    
    using ret_type = void(*)(int);
    using lambda_type = std::function<void(int)>;
    
    void HelloWorld(const char *);
    
    static inline void* fn(void* new_fn) {
        static void * fn;
        if (new_fn != nullptr) {
            fn = new_fn;
        }
        
        return fn;
    }
    
    template<typename R, typename T, typename... Args>
//    static inline void lambda_ptr_exe(int data) {
    static inline R lambda_ptr_exe(Args... data) {
        void* c_fn = fn(nullptr);
//        lambda_type* l_fn = reinterpret_cast<lambda_type*>(c_fn);
        T* l_fn = reinterpret_cast<T*>(c_fn);
        return static_cast<R>((*l_fn).operator()(std::forward<Args>(data)...));
    }
    
    template<typename... Args, typename T>//, bool = std::is_void<Args...>::value>
    static inline auto ptr(T&& t) {
        using R = decltype(std::declval<T>()(std::declval<Args>()...));
        using RetType = R(*)(Args...);
        fn(reinterpret_cast<void*>(&t));
        
        return static_cast<RetType>(lambda_ptr_exe<R, std::decay_t<T>, Args...>);
    }
    
    template<typename... Args, typename T>
    auto ptr_2(T& t) {
        using R = decltype(std::declval<T>()(std::declval<Args>()...));
          
    }
};

#pragma GCC visibility pop
#endif
