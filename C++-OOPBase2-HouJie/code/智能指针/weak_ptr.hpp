#pragma once
#include "shared_ptr.hpp"
#include <stdexcept>  
using namespace std;

template<typename T>
class weak_ptr {
public:
    // 1. 默认构造
    weak_ptr(): ptr(nullptr), cb(nullptr) {}

    // 2. 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& s): ptr(s.ptr), cb(s.cb){
        if(this->cb) this->cb->weak_count++;
    }

    // 3. 拷贝构造
    weak_ptr(const weak_ptr& other): ptr(other.ptr), cb(other.cb){
        if(this->cb) this->cb->weak_count++;    //这里应该不用管shard_count吧?
    }

    // 4. 赋值 (shared_ptr)
    weak_ptr& operator=(const shared_ptr<T>& s){
        if(this->ptr != s.ptr){
            release();
            this->ptr = s.ptr;
            this->cb = s.cb;
            if(this->cb) this->cb->weak_count++;
        }
        return *this;
    }

    // 5. 赋值 (weak_ptr)
    weak_ptr& operator=(const weak_ptr& other){
        if(this->cb != other.cb){
            release();
            this->ptr = other.ptr;
            this->cb = other.cb;
            if(this->cb) this->cb->weak_count++;
        }
        return *this;
    }

    // 6. 析构
    ~weak_ptr(){
        release();
    }

    // 7. 判断对象是否已销毁
    bool expired(){
        return !this->cb || this->cb->shared_count == 0;           
    }

    // 8. 提升为 shared_ptr
    shared_ptr<T> lock() {
        if(this->cb && this->cb->shared_count > 0){
            return shared_ptr<T>(this->ptr, this->cb);
        }
        else return shared_ptr<T>();
    }

    //移动赋值
    weak_ptr& operator=(weak_ptr&& other) {
        if(this != &other){
            release();
            this->ptr = other.ptr;
            this->cb = other.cb;
            other.ptr = nullptr;
            other.cb = nullptr;
        }
        return *this;
    }

private:
    T* ptr;         // 为了方便 lock 时快速获取对象指针（虽然可能已失效）
    ControlBlock* cb;

    //weak_ptr释放的时候不用管ptr, 但是需要减小控制块的weak_count.
    void release(){
        if(this->cb){
            this->cb->weak_count--;
            if(this->expired() && this->cb->weak_count <= 0){
                delete cb;
                this->cb = nullptr;
            }
        }
    }
};