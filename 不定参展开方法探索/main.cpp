//
//  main.cpp
//  不定参展开方法探索
//
//  Created by cdr on 2022/7/26.
//

#include <iostream>


//思考，一直以来都是不定参作为实际参数，又没可能作为类型呢？不作为参数
//结果参考 打印函数类型 target
//使用的是 递归方式
/*
 递归方式展开不定参数
 这种无法使用
 template<typename T>
 void test_t() {}
 
 template<typename F, typename... Args>
 void test_t() {}
 
 test_t<int, char, int>();//error
 */
template<typename T>
void test_t(const T& p) {
    std::cout << p << std::endl;
}

template<typename F, typename... Args>
void test_t(const F& f, const Args&... args) {
    test_t(f);
    test_t(args...);
}

/*
 逗号运算符扩展
 暂时没找到，也不行 test_expand<int, char, int>();//error
 */
template<typename T>
void test_t_e(T& t) {
    std::cout << t << std::endl;
}

template<typename... Args>
void test_expand(Args... args) {
    std::initializer_list<int> {(test_t_e(args), 0)...};
}

/*
 结合 type_traits
 */
template<std::size_t I = 0, typename Tuple>
typename std::enable_if_t<I == std::tuple_size_v<Tuple>> test_tuple(Tuple tuple) {
    
}

template<std::size_t I = 0, typename Tuple>
typename std::enable_if_t< I < std::tuple_size_v<Tuple> > test_tuple(Tuple tuple) {
    std::cout << typeid(decltype(std::get<I>(tuple))).name() << std::endl;
    test_tuple<I + 1>(tuple);
}

template<typename... Args>
void test_type(Args... args) {
    test_tuple(std::make_tuple(args...));
//    test_tuple(std::make_tuple(std::declval<Args>()...));
}


//类扩展方式

//模板带参数
template<int n>
class Sum {
public:
    enum { N = Sum<n - 1>::N + n };
};

template<>
class Sum<0> {
public:
    enum { N=0 };
};

//继承构造函数 方式
template<int...>
struct IndexSeq {};

template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};

/*
 上面如果使用 MkeIndxes<3>::type 展开如下
 
 template<int ...>
 struct IndexSeq
 {
 };

 //最初调用的继承关系，也是递归的开始
 // 对应上  struct MakeIndexes<3> : public MakeIndexes<2, 2>
 // 首先之前学习 模板不定参的时候知道。typename... Args 或者。int ...i 是允许空的
 // 也就是 MakeIndexes<3>::type 调用的时候 MakeIndexes<3> 对应的就是 N == 3，Indexes.. 是空
 // 接着查看继承构造函数。public MakeIndexes<N - 1, N - 1, Indexes...> 对应上 public MakeIndexes<2, 2>
 // 去到 struct MakeIndexes<2, 2> : public MakeIndexes<1, 1, 2>
 // 根据递归展开规则 N == 2, Indexes.. 是 2
 // 继承构造函数 public MakeIndexes<1, 1, 2>，
 //  struct MakeIndexes<1, 1, 2> : public MakeIndexes<0, 0, 1, 2> , 这里展开 对应的就是。N == 1， Indexes.. 是 1, 2
 // 继承构造 public MakeIndexes<0, 0, 1, 2>, N == 0， Indexes.. 是 0, 1, 2
 // 也是最后一次展开，为什么呢,注意到没有。此时 N == 0
 // 跑到了终止递归了。struct MakeIndexes<0, Indexes... >， 这里 N == 0
 // 此时，结果不断累积， 就附着到 Indexes... 中，此时也是在终止类里进行操作 using type = IndexSeq<Indexes...>; -》 using T = MakeIndexes<3>::IndexSeq<0, 1, 2>;
 
 //终结：一个递归变化的类，一个终止类，终止类 做操作，同时添加辅助 不定参类。
 // 继承 两次 N - 1 不是bug, 而是为了 一次给 下一次的 N，一次 作为下一次 实际的开始
 
 template<int N, int ...Indexes>
 struct MakeIndexes : public MakeIndexes<N - 1, N - 1, Indexes...>
 {
 };

 
 //第二次展开
 #ifdef INSIGHTS_USE_TEMPLATE
 template<>
 struct MakeIndexes<2, 2> : public MakeIndexes<1, 1, 2>
 {
 };

 #endif
 
 //第三次展开
 #ifdef INSIGHTS_USE_TEMPLATE
 template<>
 struct MakeIndexes<1, 1, 2> : public MakeIndexes<0, 0, 1, 2>
 {
 };

 #endif
 
 //最后一次展开
 #ifdef INSIGHTS_USE_TEMPLATE
 template<>
 struct MakeIndexes<0, 0, 1, 2>
 {
   using type = IndexSeq<0, 1, 2>;
 };

 #endif
 
 //第一次展开
 #ifdef INSIGHTS_USE_TEMPLATE
 template<>
 struct MakeIndexes<3> : public MakeIndexes<2, 2>
 {
 };

 #endif

//结束递归
 template<int ...Indexes>
 struct MakeIndexes<0, Indexes... >
 {
   using type = IndexSeq<Indexes...>;
 };

 */
//还有一种using 方式


//思考， 一直都是递归的，各做各的，有没有办法多次结果结合在一起最终输出 ？？
//参考 类继承构造展开 重点的辅助 不定参 类
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "递归方式：" << std::endl;
    test_t(32, 33.0, "ca");
    std::cout << "逗号方式：" << std::endl;
    test_expand(32, 33.0, "ca");
    
    std::cout << "结合 type_traits：" << std::endl;
    test_type(32, 33.0, "ca");
    
    
    //    int num = 100;//Non-type template argument is not a constant expression
    constexpr int num = 100;
    std::cout << "模板计算：" << num << "! -> " << Sum<num>::N << std::endl;
    
    
    using T = MakeIndexes<3>::type; // 这里得到的是 using T = MakeIndexes<3>::IndexSeq<0, 1, 2>;
    
    return 0;
}
