//
//  main.cpp
//  String_View
//
//  Created by cdr on 2022/6/5.
//

#include <iostream>

using namespace std;

string greet(string_view name) {//string_view 不要作死返回
    string ret("Hi, ");
    ret += name;
    ret += " !";
    
    return ret;
}

/*
 我们可以使用 greet(const string&) 这样的按引用传参方式。这样的参数形式对 string 实参当然很友好，但对于字符串字面量就不友好了。虽然使用字符串字面量看起完全自动很正常，但编译器产生的代码是相当无聊和低效的：它会生成一个临时 string 对象，把字符串字面量中的内容全部复制进去，然后拿这个临时对象去调用 greet 函数，并在函数返回之后销毁这个临时的 string 对象。我们可以使用 greet(const char*) 这样的传统接口。这样的参数形式对字符串字面量实参很友好，但对 string 对象来讲，就不方便了——我们会需要使用 s.c_str() 这样的形式来传参。还有，如果这个字符串很长，获取字符串的长度也会是一个低效的 O(n) 操作。此外，我们也没法直接使用 string 类提供的方便方法了，如 find、substr 等。
 
 当我们传递的实参为 string 时，string 会使用内部指针和长度高效地生成 string_view 对象。当我们传递的实参可退化为 const char* 时，那编译器会自动获取这个字符串的长度（通过调用 char_traits<char>::length(s)）。这里又可以细分为两种情况：字符串内容在编译时确定（即字符串字面量），及字符串内容在编译时不确定。当字符串内容在编译时可确定时，string_view 具有最大的优势：不仅我们没有任何额外的开销，而且目前的主流优化编译器都可以在编译时算出字符串的长度，因而可以产生最高效的代码。否则，string_view 会在代码执行时去动态获取字符串的长度，在你后续需要字符串长度时也非常合适，不算额外开销。
 */
int main(int argc, const char * argv[]) {
    // insert code here...
    auto ret = greet("cdr");
    //最好不要用字面量 "..."s; 在这行语句执行结束时，临时 string 对象就已经不存在 最终结果也许正确也许内存泄漏
    string_view temp = "temp test"s;//Object backing the pointer will be destroyed at the end of the full-expression
    string rr = greet(temp);//这样用法稍微跟上面不一样，因为实际临时值是在 greet之后
    auto len = char_traits<char>::length("cdr ac\n");
    std::cout << "Hello, World!\n"
        << len << endl
        << rr << "\n"
        << ret
        << endl;
    return 0;
}
