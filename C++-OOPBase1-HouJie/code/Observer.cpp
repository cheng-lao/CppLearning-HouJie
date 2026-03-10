#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
// 观察者模式 ==  委托 + 继承
// 观察者是Subject中 有Observer这个类（委托）
// 同时这个Observer作为父类也可以被继承(继承)
// 易于添加新观察者
// 1. 观察者接口
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

// 2. 具体观察者
class ConcreteObserver : public Observer {
    std::string name;
public:
    ConcreteObserver(const std::string& name) : name(name) {}
    
    void update(const std::string& message) override {
        std::cout << name << " 收到消息: " << message << std::endl;
    }
};

// 3. 主题（被观察者）
class Subject {
    std::vector<Observer*> observers;  // 委托：管理观察者列表
    std::string state;
    
public:
    // 添加观察者（注册）
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    // 移除观察者（取消注册）
    void detach(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    // 通知所有观察者
    void notify() {
        for (Observer* observer : observers) {
            observer->update(state);
        }
    }
    
    // 状态改变时触发通知
    void setState(const std::string& newState) {
        state = newState;
        notify();  // 状态变化时自动通知
    }
};

// 使用示例
int main() {
    Subject newsPublisher;
    
    ConcreteObserver subscriber1("订阅者1");
    ConcreteObserver subscriber2("订阅者2");
    
    // 订阅（添加观察者）
    newsPublisher.attach(&subscriber1);
    newsPublisher.attach(&subscriber2);
    
    // 发布新闻，自动通知所有订阅者
    newsPublisher.setState("重大新闻：C++23发布！");
    
    // 取消订阅
    newsPublisher.detach(&subscriber1);
    
    newsPublisher.setState("另一条新闻...");
    
    return 0;
}