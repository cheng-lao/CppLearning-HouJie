

// SingleTon mode methods 单例模式
class A
{
private:
    A();
    A(const A& rhs);
public:
    static A& getinstance();
    void setup() {  }
    // ~A();
};

A::A() {}

A& A::getinstance(){
    static A a;
    return a;    
}