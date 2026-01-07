#pragma once
#include <stdexcept>  
using namespace std;

template<typename T>
class unique_ptr {
public:
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator==(const unique_ptr&) = delete;
    unique_ptr(): ptr(nullptr){}
    explicit unique_ptr(T* p): ptr(p) {}
    unique_ptr(unique_ptr&& other) noexcept{
        this->ptr = other.ptr;
        other.ptr = nullptr;
    }
    ~unique_ptr(){
        delete ptr;
    }
    unique_ptr& operator=(unique_ptr&& other) noexcept{
        if(this != &other){
            delete this->ptr;   //自己此时已近有了指向的内容，需要删除
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    operator bool() const noexcept{
        return this->ptr != nullptr;
    } 

    // 作用：切断指针与 unique_ptr 的联系，返回原始指针，不调用 delete
    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T& operator*() const{
        return *ptr;
    }
    T* operator->() const{
        return ptr;
    }
    T* get() const{
        return ptr;
    }
    void reset(T* p = nullptr){
        if(p != this->ptr){
            delete this->ptr;
            ptr = p;
        }
        else throw invalid_argument("reset with same pointer would cause dangling pointer");
    }
private:
    T* ptr;
};
