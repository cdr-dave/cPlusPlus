//
//  main.cpp
//  operator 学习
//
//  Created by cdr on 2022/7/21.
//
/*
 operator  重载操作符
功能很强大
 除了 () 都不能缺省 参数
 可以 针对普通的 + / - && || &= *= 等， operator +
 也可以针对 bool, ++ operator bool(), 后缀 operator++(int) 前缀 operator++
 重载操作符是类成员，那么只有当与 它的左操数是该类的对象时
 
 外部使用的 对于全局重载操作符，代表左操作数的参数必须被显式指定
 operator<<(std::ostream&, class&)
 进一步 有趣的地方。字面量 系统的。using namespace std::literals;
 
 当然进一步的使用 如 new new[] delete delete[] 可以作为 内存检查中
 
 还有个有趣的重载操作符
 重载 函数指针 //让对象可以赋值给函数指针
 */
#include <iostream>

//using namespace std::literals;


//下面是全局的 operator new
//void* operator new(size_t size, int tag) {
////    std::cout << "__CUSTOM_NEW_FUNC__" << std::endl;
//    printf("__CUSTOM_NEW_FUNC__\n");
//    void* ptr = malloc(size);
//    if (ptr == nullptr) {
//        throw std::bad_alloc();
//    }
//
//    return ptr;
//}
//
//void operator delete(void* ptr) noexcept
//{
////    std::cout << "__CUSTOM_DELETE_FUNC__" << std::endl;
//    printf("__CUSTOM_DELETE_FUNC__\n");
//    free(ptr);
//}
//
//void* operator new[](size_t size)
//{
//    return operator new(size);
//}
//
//void operator delete[](void* ptr) noexcept
//{
//    operator delete(ptr);
//}


//可以局部operator new
class OClass {
public:
    OClass(int n) : data(n), isInit(true) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    OClass()  {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
//    OClass() = default;
    
    int operator+(const OClass& oc) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return this->data + oc.data;
    }
    
    OClass& operator++() {
        this->data++;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }
    
    OClass operator++(int) {
        auto temp = *this;
        this->data++;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return temp;
    }
    
    inline bool operator == (const OClass &ps) {
        return this->data == ps.data;
    }
    
    inline bool operator != (const OClass &ps) {
        return !(*this == ps);
    }
    
    operator bool() {
        return isInit;
    }
    
//    friend std::ostream operator <<(std::ostream out, const OClass& oc);
    friend std::ostream& operator<<(std::ostream&out, const OClass& tmp) {
        out << tmp.data;
        return out;
    }
    
    
    void* operator new(size_t size, std::string tag) {
    //    std::cout << "__CUSTOM_NEW_FUNC__" << std::endl;
        printf("__CUSTOM_NEW_FUNC__22222\n");
        void* ptr = malloc(size);
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        
        return ptr;
    }

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
        std::cout << __PRETTY_FUNCTION__ << ", size is " << size << std::endl;
        return ::operator new(size);//调用全局的
    }

    void operator delete[](void* ptr) noexcept
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        ::operator delete(ptr);
    }
    
private:
    
    int data;
    bool isInit = false;
};

//std::ostream& operator <<(std::ostream& out,  OClass& oc) {
//    out << oc.getData();
//    return out;
//}

OClass operator ""_cc(unsigned long long i) {//没法 int  unsigned long long, 或者 long double
    return OClass(i);
}

void callFunc(const OClass& cl) {
    std::cout << cl << std::endl;
}

void i_b_func(int i, bool b) {
    std::cout << __PRETTY_FUNCTION__ << "," << i << "," << (b ? "true" : "false") << std::endl;
}

//auto lam = [](int a, bool b) {
//    std::cout << __PRETTY_FUNCTION__ << " === " << a << "," << b << std::endl;
//};
//
//using retType2 = void (*)(int, bool);
//
//operator retType2 () {//Conversion function must be a non-static member function 必须是成员函数
////    return lam;
//    return i_b_func;
//}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    OClass oc0(1), oc1 = 20, oc2;
    if (oc0) oc0++;
    if (!oc2) {
        std::cout << "oc2 not init" << std::endl;
    }
    
    if (oc0 != oc1) {
        std::cout << "oc0 != oc1" << std::endl;
    }
    
    ++oc1;
    ++oc1++; // ++(oc1++)
    //OClass OClass::operator++(int)
    //OClass &OClass::operator++()
    int num = oc0 + oc1;
    std::cout << "ret is: " << num << std::endl;
    
    callFunc(32_cc);
    
    //有部分文档说是没有构造函数调用，只有内存/ 测试发现是有点 （Xcode clang) 在 linux gcc 中一样有构造 （vs msvc 也是)
    auto oc_p0 = new(32) OClass(8);//__CUSTOM_NEW_FUNC__   OClass::OClass(int)
    auto oc_p1 = new("ff") OClass();
    auto oc_p2 = new("kkk") OClass;// __CUSTOM_NEW_FUNC__22222   OClass::OClass()
    
    delete oc_p0;
    delete oc_p1;
    
    auto oc_pa = new OClass[3]();//static void *OClass::operator new[](size_t), size is 12 //接着 3个 OClass::OClass()
    delete [] oc_pa;
    
//    int * ptr = new int; //与 new int() 没啥区别
//    int* iptr = new int(11);
//    std::cout << "new data is: " << *iptr << std::endl;
//    delete iptr;
    
    
    /*
     重载函数指针
     */
    
    class __lam {
    public:
       
        using retType = void (*)(int, bool);
//        operator retType () {
//            return s_c_func; // 必须返回 static :Reference to non-static member function must be called , 因为重载的retType 就是 没对象指针的
//        }
        
        operator retType () { //让对象可以赋值给函数指针
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            return i_b_func;
        }
        
//        operator retType () {
//            return lam;//error Reference to local variable 'lam' declared in enclosing function 'main'
//        }
        
        static void s_c_func(int, bool) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
    };
    
    std::cout << "------" << std::endl;
    void (*ibCall)(int, bool) = lc;
    
    ibCall(3, false);
    std::cout << "------" << std::endl;
    
    return 0;
}
