#include<iostream>
#include<list>
using namespace std;

class A{
public:
    virtual void vfunc1() { cout<< "this is A's vfunc1 "<<endl; }
    virtual void vfunc2() { cout<< "this is A's vfunc2 "<<endl; }
    void func1() { cout<< "this is A's func1"<<endl; }
    void func2() { cout<< "this is A's func2"<<endl; }
private:
    int m_data1, m_data2;
};

class B : public A{
public:
    void vfunc1() override {
        cout<< "this is B's vfunc1" << endl;
    }
    void func2() {
        cout<< "this is B'func2"<<endl;
    }
private:
    int m_data3;
};

class C: public B{
public:
    virtual void vfunc1(){
        cout<< "this is C's vfunc2 "<<endl;
    }

    // @override
    void func1(){
        cout<< "this is C's func1 "<<endl;
    }

private:
    int m_data4;
};

int main(int argc, char const *argv[])
{

    A a = C();
    A* ap = new C();
    ap->func1();
    ap->func1();
    ap->vfunc1();
    ap->vfunc2();
    // 查看对象 a 的虚指针内容
    void** vptr_a = (void**)(void*)&a;
    cout << "vptr of a: " << vptr_a << endl;

    // 查看指针 ap 的虚指针内容
    void** vptr_ap = (void**)(void*)ap;
    cout << "vptr of ap: " << vptr_ap << endl;
    cout << ((vptr_ap)[0]) << endl;

    cout<<" sizeof(a) is " <<sizeof(a)<<endl;
    cout<<" sizeof(ap) is "<<sizeof(ap)<<endl;

    return 0;
}
