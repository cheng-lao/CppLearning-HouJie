#pragma once
#include <stdexcept>

namespace cyj {

template<typename T>
class unique_ptr {
public:
    unique_ptr(const unique_ptr&) = delete;             // 删除拷贝构造
    unique_ptr& operator=(const unique_ptr&) = delete;  // 删除拷贝赋值
    unique_ptr(): ptr(nullptr){}
    explicit unique_ptr(T* p): ptr(p) {}
    unique_ptr(unique_ptr&& other) noexcept{            // 移动构造函数
        this->ptr = other.ptr;
        other.ptr = nullptr;
    }
    ~unique_ptr(){
        delete ptr;
    }
    unique_ptr& operator=(unique_ptr&& other) noexcept{ // 移动赋值构造函数
        if(this != &other){
            delete this->ptr;   //自己此时已近有了指向的内容，需要删除
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    operator bool() const noexcept{                     // 判断是否存在
        return this->ptr != nullptr;
    } 

    // 作用：切断指针与 unique_ptr 的联系，返回原始指针，不调用 delete
    T* release() noexcept {                             // 释放并返回指针
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T& operator*() const{           // 返回数据引用
        return *ptr;
    }
    T* operator->() const{          // 返回数据指针方便箭头函数
        return ptr;
    }
    T* get() const{                 // 返回指针
        return ptr;
    }
    void reset(T* p = nullptr){     // 回收之前的数据空间，并且重置指针
        if(p != this->ptr){
            delete this->ptr;
            this->ptr = p;
        }
        else throw std::invalid_argument("reset with same pointer would cause dangling pointer");
    }
private:
    T* ptr;         // data域只有一个数据指针
};
}
