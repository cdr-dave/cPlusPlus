//
//  main.cpp
//  迭代器
//
//  Created by cdr on 2022/5/6.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class operatorAdd {
public:
    
    operatorAdd() = default;
    
    operatorAdd(int n) : num(n) {
        
    }
    
    operatorAdd& operator++() {//前缀 ++i
        cout << __PRETTY_FUNCTION__ << endl;
        ++(this->num);
        return *this;
    }
    
    const operatorAdd operator++(int) {//后缀 i++
        auto oldN = *this;
        ++*this;
        
        cout << __PRETTY_FUNCTION__ << endl;
        return oldN;
    }
    
    friend ostream& operator<<(ostream&out, operatorAdd& tmp) {
        cout << tmp.num;
        return out;
    }
    
private:
    int num = 100;
};

namespace myTest
{

class mIterator : public std::iterator<input_iterator_tag, string> {
public:
    mIterator() = default;
    mIterator(int start, int limit = 20) : tag(start), limit(limit) {}
    
    const int& operator*() {
        return tag;
    }
    
//    int* operator->() {
//        return &tag;
//    }
//
    mIterator& operator++() {
        ++this->tag;
        if (this->tag >= this->limit) {
            this->tag = -1;
        }
        
        return *this;
    }
    
//    const mIterator operator++(int) {
//        auto tmp = mIterator(this->tag);
//        ++(*this);
//        return tmp;
//    }
    
//    bool operator==(const mIterator& iter) {
//        return this->tag == iter.tag;
//    }
    
    bool operator!=(const mIterator& iter) {
//        return !(operator==(iter));
        return this->tag != iter.tag;
    }
    
private:
    int tag = -1;
    int limit = 0;
};


class Data_reader {
public:
    
};

mIterator begin(Data_reader& reader) {
    return mIterator(0);
}

mIterator end(Data_reader& reader) {
    return mIterator();
}




};

class istream_line_reader {
public:
    class iterator {// : public std::iterator<input_iterator_tag, string> {
    public:
        
        typedef string        value_type;
        typedef ptrdiff_t  difference_type;
        typedef value_type*   pointer;
        typedef value_type& reference;
        typedef input_iterator_tag  iterator_category;
        
        iterator() noexcept
        : stream_(nullptr) {}
        
        explicit iterator(istream& is) : stream_(&is) {
            ++*this;
        }
        
        const string& operator*() const noexcept {
            return line_;
        }
        
        const string* operator->() const noexcept {
            return &line_;
        }
        
        iterator& operator++() {
            if (stream_ == nullptr) {
                ++iTag;
                if (iTag < arrTest.size()){
                line_ = arrTest[iTag];
                    
                }
                else//越界后要跟 end() 也就是iterator()比较
                {
                    iTag = -1;
                }
                
                return *this;
            }
            
            getline(*stream_, line_);
//            getline(*stream_, line_);
            if (!*stream_) {
                stream_ = nullptr;
            }
            
            return *this;
        }
        
        const iterator operator++(int) {
            iterator temp(*this);
            ++*this;
            return temp;
        }
        
        bool operator==(const iterator& rhs) const noexcept {
            return iTag == rhs.iTag;
//            return stream_ == rhs.stream_;
        }
        
        bool operator!=(const iterator& rhs) const noexcept {
            return !operator==(rhs);
        }
        
    private:
        istream* stream_ = nullptr;
        string line_;
        
        int iTag = -1;
        vector<string> arrTest {"a", "bb", "ccc"};
    };
    
    istream_line_reader() noexcept
        : stream_(nullptr) {}

    explicit istream_line_reader(istream& is) noexcept
        : stream_(&is) {}
    
    iterator begin() {
        return iterator(*stream_);
    }
    
    iterator end() noexcept {
        return iterator();
    }
    
private:
    istream* stream_;
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    operatorAdd add_0(1);
    add_0++;
    cout << "add_0++:" << add_0 << endl;
    ++add_0;
    cout << "++add_0:" << add_0 << endl;
    
//    stringbuf buf;
//    filebuf buf;
//    istream is(&buf);
    
    for (const string& line :
         istream_line_reader()) {
      // 示例循环体中仅进行简单输出
      cout << line << endl;
    }
    
    for (auto tag : myTest::Data_reader()) {
        cout << "test: " << tag << endl;
    }
    
    return 0;
}
