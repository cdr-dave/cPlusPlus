//
//  main.cpp
//  多线程——避免死锁
//
//  Created by cdr on 2022/5/24.
//

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

//层次锁 使用层次锁结构:如下, 定义锁的不同层次, 只能高层获取低层的锁, 保证锁的顺序
//说白了就是在同一线程中锁定的层次值只能依次递减
class hierarchical_mutex
{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
    
    void check_for_hierarchy_violation()
    {
        if (this_thread_hierarchy_value <= hierarchy_value)
        {
            throw  std::logic_error("mutex hierarchy violated");//逻辑错误 std::domain_error 专业错误 // 运行时错误 std::runtime_error
        }
    }
    
    void update_hierarchy_value()
    {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

public:
    explicit hierarchical_mutex(unsigned long value) : hierarchy_value(value), previous_hierarchy_value(0) {
        
    }
    
    void lock() {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }
    
    void unlock() {
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }
    
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock()) return false;
        
        update_hierarchy_value();
        
        return true;
    }
    
    static unsigned long get_thread_hierarchy_value()
    {
        return this_thread_hierarchy_value;
    }
};

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

hierarchical_mutex h_l_mutex(1000);
hierarchical_mutex l_l_mutex(500);

int do_low_level_stuff() {
    return 1;
}

int low_level_func() {
    //lock_guard 是通过模板实现的编译时期多态
    std::lock_guard<hierarchical_mutex> lk(l_l_mutex);
    return do_low_level_stuff();
}

void high_level_stuff(int some_pram) {
    
}

void high_level_func() {
    std::lock_guard<hierarchical_mutex> lk(h_l_mutex);
    high_level_stuff(low_level_func());
}

void err_level_func() {
    std::lock_guard<hierarchical_mutex> ek(l_l_mutex);
    high_level_func();
    low_level_func();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    high_level_func();
    try
    {
        err_level_func();
    }
    catch (exception& e) {//excetion e  这样 赋值操作， e.what 得不到结果 应该没有拷贝函数
        cout << e.what() << ", " << typeid(e).name() << std:: endl;//mutex hierarchy violated, St11logic_error
    }
    
    return 0;
}
