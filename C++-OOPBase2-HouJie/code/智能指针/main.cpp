#include <iostream>
#include "shared_ptr.hpp"
#include "unique_ptr.hpp" // 保留 unique_ptr 用于对比
#include "weak_ptr.hpp"
#include <stdexcept>  
void test_1();

// 测试用类
class Test {
public:
    Test() { std::cout << "Test 构造\n"; }
    ~Test() { std::cout << "Test 析构\n"; }
    void hello() { std::cout << "Hello 智能指针!\n"; }
};


int main(int argc, char const *argv[])
{
    // --- Unique Ptr 测试  ---
    std::cout << "--- unique_ptr 演示 ---\n";
    cyj::unique_ptr<Test> up1(new Test());
    up1->hello();
    cyj::unique_ptr<Test> up2 = std::move(up1); 
    if (!up1.get()) std::cout << "up1 已失去所有权\n";
    up2->hello();

    // --- Shared Ptr 测试 ---
    std::cout << "\n--- shared_ptr 演示 ---\n";
    cyj::shared_ptr<Test> sp1(new Test());
    std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 1
    {
        cyj::shared_ptr<Test> sp2 = sp1;
        std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 2
        sp2->hello();
    } // sp2 析构，引用计数减 1
    std::cout << "sp1 use_count: " << sp1.use_count() << "\n"; // 1

    // --- Weak Ptr 测试 (重点) ---
    std::cout << "\n--- weak_ptr 演示 ---\n";
    
    // 1. 创建 shared_ptr
    cyj::shared_ptr<Test> wsp1(new Test());
    
    // 2. 用 weak_ptr 观测它
    cyj::weak_ptr<Test> wp1(wsp1);
    
    std::cout << "wp1 expired? " << (wp1.expired() ? "Yes" : "No") << "\n"; // No
    
    // 3. 尝试 lock() 获取使用权
    if (auto temp_sp = wp1.lock()) {
        std::cout << "Lock 成功，正在使用对象...\n";
        temp_sp->hello();
        std::cout << "temp_sp use_count: " << temp_sp.use_count() << "\n"; // 2 (wsp1 + temp_sp)
    }

    // 4. 销毁原始的 shared_ptr
    std::cout << "释放 wsp1...\n";
    wsp1 = cyj::shared_ptr<Test>(nullptr);
    // 此时 Test 对象应该被析构，但 ControlBlock 还在，因为 wp1 还在引用它

    // 5. 再次检测 expired
    std::cout << "wp1 expired? " << (wp1.expired() ? "Yes" : "No") << "\n"; // Yes
    
    // 6. 再次尝试 lock
    if (auto temp_sp2 = wp1.lock()) {
        temp_sp2->hello();
    } else {
        std::cout << "对象已被销毁，lock 失败，无法访问\n";
    }

    std::cout << "\n--- unique_ptr reset 演示 ---\n";
    cyj::unique_ptr<Test> up_reset(new Test());
    up_reset->hello();
    std::cout<< "...."<< std::endl;
    // 正常 reset
    up_reset.reset(new Test());
    up_reset->hello();

    // 潜在问题测试：传入相同指针
    Test* raw = up_reset.get();
    // up_reset.reset(raw);  // 在标准实现中，这里会删 raw，然后 up_reset 指向已删内存 -> UB（可能 crash 或 hello() 出错）
    up_reset->hello();    // 如果用安全版，这里不会删，hello() 正常

    test_1();

    return 0;
}

void test_1(){
    // --- Shared Ptr 移动测试 ---
    std::cout << "\n--- shared_ptr 移动演示 ---\n";
    cyj::shared_ptr<Test> sp_move(new Test());
    std::cout << "sp_move use_count: " << sp_move.use_count() << "\n"; // 1
    cyj::shared_ptr<Test> sp_move2 = std::move(sp_move);
    std::cout << "sp_move2 use_count: " << sp_move2.use_count() << "\n"; // 1
    if (!sp_move) std::cout << "sp_move 已失去所有权\n";  // output 

    // --- Reset 测试 ---
    std::cout << "\n--- shared_ptr reset 演示 ---\n";
    sp_move2.reset(new Test());
    sp_move2->hello();
    sp_move2.reset();  // 释放

    // --- 循环引用演示（weak_ptr 作用） ---
    std::cout << "\n--- 循环引用演示 ---\n";
    class Node {
    public:
        cyj::shared_ptr<Node> next;
        cyj::weak_ptr<Node> prev;  // 用 weak 打破循环
        ~Node() { std::cout << "Node 析构\n"; }
    };

    {
        cyj::shared_ptr<Node> node1(new Node());
        cyj::shared_ptr<Node> node2(new Node());
        node1->next = node2;
        node2->prev = node1;  // 如果 prev 是 shared_ptr，会循环不析构
    }  // 出作用域，应析构两个 Node
}