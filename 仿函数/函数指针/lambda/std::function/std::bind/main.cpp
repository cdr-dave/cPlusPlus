//
//  main.cpp
//  仿函数/函数指针/lambda/std::function/std::bind
//
//  Created by cdr on 2022/7/19.
//

#include <iostream>
#ifndef __MSC_VER
#include <cxxabi.h>
#endif
//#include <codecvt>

//可以 void(void*)
struct Lambda {
    template<typename Tret, typename T>
    static Tret lambda_ptr_exec(void* data) {
        return (Tret) (*(T*)fn<T>())(data);
    }

    template<typename Tret = void, typename Tfp = Tret(*)(void*), typename T>
    static Tfp ptr(T& t) {
        fn<T>(&t);
        return (Tfp) lambda_ptr_exec<Tret, T>;
    }

    template<typename T>
    static void* fn(void* new_fn = nullptr) {
        static void* fn;
        if (new_fn != nullptr) {
            fn = new_fn;
        }

        return fn;
    }
};



//调整 Lambda 扩展开来，改为 void(int)
//本质上依旧是属于 静态存储再转换的形式，也就是再上一次触发前，不能调用
struct Lambda_c
{
    //原模板代码
//    template<typename Tret, typename T>
//    static Tret lambda_ptr_exec(void* data) {
//        return (Tret) (*(T*)fn<T>())(data);
//    }
//
//    template<typename Tret = void, typename Tfp = Tret(*)(void*), typename T>
//    static Tfp ptr(T& t) {
//        fn<T>(&t);
//        return (Tfp) lambda_ptr_exec<Tret, T>;
//    }
//
//    template<typename T>
//    static void* fn(void* new_fn = nullptr) {
//        static void* fn;
//        if (new_fn != nullptr) {
//            fn = new_fn;
//        }
//
//        return fn;
//    }
    
    //模板展开后代码
//    using __lambda_60_14 = std::function<void(void*)>;

//  template<>
//  static inline void lambda_ptr_exec<void, __lambda_60_14>(void * data)
//  {
//    return static_cast<void>((*reinterpret_cast<__lambda_60_14 *>(fn<__lambda_60_14>(nullptr))).operator()(data));
//  }
//
//  template<>
//  static inline void (*ptr<void, void (*)(void *), __lambda_60_14>(__lambda_60_14 & t))(void *)
//  {
//    fn<__lambda_60_14>(reinterpret_cast<void *>(&t));
//    return static_cast<void (*)(void *)>(lambda_ptr_exec<void, __lambda_60_14>);
//  }
//
//  template<>
//  static inline void * fn<__lambda_60_14>(void * new_fn)
//  {
//    static void * fn;
//    if(new_fn != nullptr) {
//      fn = new_fn;
//    }
//
//    return fn;
//  }
    
    //调整优化代码
    using lambda_11 = std::function<void(int)>;
    
    static inline void* c_fn(void* new_fn) {
        static void * fn;
        if(new_fn != nullptr) {
          fn = new_fn;
        }
        
        return fn;
    }
    
    static inline void c_lambda_ptr_exec(int data) {
        return static_cast<void>(  ( *( reinterpret_cast<lambda_11 *>(c_fn(nullptr)) ) ).operator()(data)   );
    }
    
    //外部接口
    static inline void (*c_ptr(lambda_11& t))(int) {
        c_fn(reinterpret_cast<void *>(&t));
        return static_cast<void (*)(int)>(c_lambda_ptr_exec);
    }
    
  
};

template<typename Tret, typename T>
Tret lambda_ptr_exec(T* v) {
    return (Tret) (*v)();
}

template<typename Tret = void, typename Tfp = Tret(*)(void*), typename T>
Tfp lambda_ptr(T& v) {
//    std::cout << "T type is:" << typeid(T).name() << std::endl;
//    char * name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
//    std::cout << name << std::endl;
//    free(name);
    return (Tfp) lambda_ptr_exec<Tret, T>;
}

template<typename PType = void, typename Tret, typename T>
Tret lambda_ptr_exec2(T* v) {
    return (Tret) (*v)();
}

template<typename PType = void*, typename Tret = void, typename Tfp = Tret(*)(PType), typename T>
Tfp lambda_ptr2(T& v) {
    std::cout << "T type is:" << typeid(T).name() << std::endl;
    char * name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    std::cout << name << std::endl;
    free(name);
    return (Tfp) lambda_ptr_exec2<PType, Tret, T>;
}

/*
 根据 lambda_ptr 推导出展开（https://cppinsights.io/
 */
class c__lambda_16_18
{
public:
    inline /*constexpr */ void operator()(int i) const
    {
        std::cout << __PRETTY_FUNCTION__ << "," << i << ", a: " << a << std::endl;
    }
    
private:
    int a = 12;
};

template<typename T>
void lambda_ptr_exec3(T * v, int n)
{
  return static_cast<void>( (*v).operator()(n) );
}

template<typename T>
void (*lambda_ptr3(T & v))(int n)
{
  return reinterpret_cast< void(*)(int) >(lambda_ptr_exec3<T>);
}

//

class FuncClass {
public:
    void operator()(int i) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    void c_func(int i) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "num is: " << num << "," << "i is: " << i << std::endl;
    }
    
    int num = 12;
};


auto km(int n) -> void(*)(int) {
    FuncClass fc;
//    return std::bind(&FuncClass::c_func, &fc, std::placeholders::_1);

//    void (FuncClass::*CU_func)(int) = &FuncClass::c_func;
//    return fc.*CU_func;
    
        return [](int n) {
    //        fc.num = 222;
        };
        
}

int sum(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

//返回函数指针
int (*call_func(char c))(int, int) {
    if ('+' == c) {
        return sum;
    }
    else if ('-' == c) {
        return sub;
    }
    
    return nullptr;
}

typedef void (* MYPROC)(int);

//template<typename R, typename... Args>
//void funff(Args... args) {
//    using rett = R(Args...);
//}

template<typename R, typename... Args, typename T>
//    static inline void lambda_ptr_exe(int data) {
static inline R lambda_ptr_exe22(Args... data) {
    void* c_fn = nullptr;
    T* l_fn = reinterpret_cast<T*>(c_fn);
    return static_cast<void>((*l_fn).operator()(std::forward<Args>(data)...));
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    FuncClass fc;
    fc(32);
    
//    void (*call)(int) = fc;//不行
    
    fc.num = 333;
    
    std::function<void(int)> func = std::bind(&FuncClass::c_func, &fc, std::placeholders::_1);
    func(100);
    
    void (FuncClass::*CU_func)(int) = &FuncClass::c_func;
    int (FuncClass::*CU_num) = &FuncClass::num;
    fc.*CU_num = 111;
    (fc.*CU_func)(33);
    
    auto c = std::mem_fn(&FuncClass::c_func);
    c(&fc, 2);
    
    _VSTD::__invoke(&FuncClass::c_func, &fc, 3333);
//    void (*call)(int) = std::mem_fn(&FuncClass::c_func, &fc);//依旧没有找到 转函数指针方法 除了 lambda 不接收外部参数时候
    void (*call)(int) = [](int) {
        std::cout << "郁闷" << std::endl;
    };
//    void (*call)(int) = (fc.*CU_func);//也不行
    
    call(2);
    
    int p = 7;
    static auto f = [&](int a) {
        std::cout << fc.num << "," << p + a << std::endl;
    };
    MYPROC ff = [](int i) { return f(i); };
    
    ff(33);
    //here, it works!
//    fun(ff);

//    auto ff = [&]() -> void(*)(int) {
//        return
//    };
    
    
    
//    auto func2 = [&]() {
//        std::cout << "lambda " << fc.num << std::endl;
//    };
//
//    void (*fp)(void*) = lambda_ptr(func2);//没有报错，但是捕获不到，展开模板发现 返回的 lambda_ptr_exec 没有作为参数传递进去
//    fp(nullptr);
//
    auto func3 = [&](int n) {
    };

    call = lambda_ptr3(func3);//跟lambda_ptr 一样是没有传递引用
    call(345);
    
    int a = 100;
    auto b = [&](void*) {return ++a;};
    void (*f1)(void*) = Lambda::ptr(b); //这个捕获是成功的，但是只是针对参数 void* 的，没法自定义参数
    f1(nullptr);
    printf("a == %d\n", a);  // 101
    
    Lambda_c::lambda_11 bb = [&](int n) { a = a + n; };
    void (*f2)(int) = Lambda_c::c_ptr(bb);
    f2(10);
    printf("a == %d\n", a);  // 111
    
    auto callS = call_func('+');//测试函数指针作为返回参数的写法
    std::cout << callS(1, 3) << std::endl;
    
    {
        //网上的一种写法，
        int p = 7;
        static auto f = [&](int a) {
            auto temp = p;
           p = temp + a;
            printf("捕获结果 %d + %d = %d\n", temp, a, p);
        };
        void(*call)(int) = [](int i) { return f(i); };

        call(33);
        
        //参考 https://cppinsights.io/ 扩展开来 其实就是下面的方式，虽然没懂 return 静态匿名方法()  跟普通的 return 匿名方法 展开来差距这么奇怪
        class lam_class {
        public:
            int & pc; //引用
            lam_class() = delete;
            
            lam_class(int& p) : pc(p) {
                
            }
            
            using retType = void(*)(int);
            
            operator retType() {
                std::cout << "=======" << std::endl;
                std::cout << __PRETTY_FUNCTION__ << std::endl;
                auto temp = pc;
//                pc = temp + a;
//                printf("捕获结果 %d + %d = %d\n", temp, a, pc);
                std::cout << "捕获" << " " << pc << std::endl;
                std::cout << "=======" << std::endl;
//                static int s_p = pc;
                static lam_class* s_lc = this;
                return [](int a) {
                    std::cout << "这里没必要做啥，只是作为返回" << ",参数在这里 a = " << a << std::endl;
                    s_lc->pc ++;
                    f(a);//没办法，只能用外部静态的，当然也可以 静态对象指针 s_lc
                };
            }
            
        };
        
        lam_class lc(p);
        
        std::cout << "函数指针 operator 在赋值时触发" << std::endl;
        call = lc;
        std::cout << "--------------" << std::endl;
        call(20);
        
        //用到了静态 还是没有我想要的那种
        
        
    }
    
    
    return 0;
}
