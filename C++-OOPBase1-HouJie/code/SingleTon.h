

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
    //只有有人用过这个 类才会生成这个static对象，否则在内存当中就不会出现
    //使用方法 A::getinstance().setup();
    static A a;
    return a;    
}