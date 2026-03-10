#pragma once
#include <stdexcept>

namespace cyj {

// 前向声明
template<typename T> class weak_ptr;
// 控制块结构体
struct ControlBlock {
    int shared_count;
    int weak_count;
    ControlBlock() : shared_count(1), weak_count(0) {}
    ControlBlock(int sc, int wc) : shared_count(sc), weak_count(wc) {}
};

template<typename T>
class shared_ptr {
    // 声明 weak_ptr 为友元，以便weak_ptr访问内部的 ptr 和 cb
    friend class weak_ptr<T>;
public:
    // 1. 默认构造
    shared_ptr():ptr(nullptr), cb(nullptr) { }
    
    // 2. 指针构造
    explicit shared_ptr(T* p): ptr(p){
        if(p==nullptr) this->cb = nullptr;
        else this->cb = new ControlBlock();
    }

    // 3. 拷贝构造
    shared_ptr(const shared_ptr& other): ptr(other.ptr), cb(other.cb) {
        if(this->cb)    //如果cb存在的话
            this->cb->shared_count++;
    }
    
    // 移动构造
    shared_ptr(shared_ptr&& other) noexcept: ptr(other.ptr), cb(other.cb) {
        other.ptr =  nullptr;
        other.cb =  nullptr;
    }

    // 4. 析构函数
    ~shared_ptr(){
        release();//将当前对象的shared_count减一，
    }
    
    //判断shared_ptr是否为空
    operator bool() const noexcept{
        return this->ptr != nullptr;
    }

    // 5. 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other){
        if(this != &other){
            release();
            this->ptr = other.ptr;
            this->cb = other.cb;
            if(this->cb)    
                this->cb->shared_count++;
        }
        return *this;
    }

    // 6. 移动赋值运算函数 .operator=(std::move(shared_ptr))
    shared_ptr& operator=(shared_ptr<T>&& other) noexcept {
        if(this != &other){
            release();
            this->ptr = other.ptr;
            this->cb = other.cb;
            // 移动赋值相当于是将右值 指针值转移过来，所以这里不会增加引用计数
            // 下面两行是移动构造函数和拷贝构造函数的关键区别
            other.ptr = nullptr;
            other.cb = nullptr;
            
        }
        return *this;
    }
    
    // 常用操作符
    T& operator*() const{
        if(!this->ptr) throw std::runtime_error("Attempt to dereference a null shared_ptr");
        return *this->ptr; 
    }

    T* operator->() const {
        if(!this->ptr) throw std::runtime_error("Attempt to dereference a null shared_ptr");
        return this->ptr;
    }

    T* get() const { return this->ptr; }
    
    int use_count() const {
        if(this->cb)
            return this->cb->shared_count; 
        else return 0;
    }
    
    // depricated!
    //reset 接受一个新指针，并将当前对象指向它，并且释放当前所指得对象引用
    // void reset(T* p = nullptr){
    //     if(this->ptr == p) {
    //         throw std::runtime_error("reset with same pointer would cause dangling pointer");
    //     }
    //     if(this->cb){
    //         this->cb->shared_count--;   //自减
    //         if(this->cb->shared_count <= 0){
    //             delete this->ptr;   
    //             // delete更详细的过程是 先执行this->ptr->~class析构函数
    //             // 然后是执行operator delete()函数
    //             this->ptr = p;
    //             // 下面是一种很糟糕的实现，这里重用了控制块但是标准库当中其实是能重用控制块cb的！
    //             if(this->cb->weak_count <= 0){
    //                 /*
    //                 无论 weak_count 是否为 0，都不能重用控制块。
    //                 控制块的生命周期必须与它所跟踪的原始对象完全独立，一旦对象被销毁，
    //                 控制块只能等待所有 weak_ptr 释放，然后自身销毁，绝不能再用于其他对象。
    //                 */
    //                 delete  this->cb;
    //                 this->cb = new ControlBlock();
    //                 this->cb->shared_count = 1;
    //                 this->cb->weak_count = 0;
    //             } else{
    //                 this->cb = new ControlBlock(1, 0);
    //             }
    //         }else{
    //             this->ptr = p;
    //             this->cb = new ControlBlock();
    //         } //如果shard_count自减后 不为0
    //     }        
    // }

    void reset(T* p = nullptr) {
        shared_ptr(p).swap(*this);
    }
    
    void swap(shared_ptr& other) noexcept {
        std::swap(ptr, other.ptr);
        std::swap(cb, other.cb);
    }

private:
    T* ptr;
    ControlBlock* cb;

    // 释放资源的辅助函数
    void release(){
        if(cb){
            cb->shared_count--;
            if(cb->shared_count == 0){
                delete ptr;
                ptr = nullptr;  //存在ptr为空但是control_block不为空的情况
                // 如果此时也没有 weak_ptr 引用控制块，则销毁控制块
                if (cb->weak_count == 0) {
                    delete cb;
                    cb = nullptr;
                }
            }
        }
    }

    // 供 weak_ptr::lock() 使用的特殊构造函数，因为不允许对外界公开control_block所以这里使用私有函数
    shared_ptr(T* p, ControlBlock* control_block): 
        ptr(p), cb(control_block)
    {
        if(this->cb) this->cb->shared_count++;  
    }
};
}
