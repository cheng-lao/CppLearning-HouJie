#include <iostream>
using namespace std;

/*
operator new 调用情况，使用表达式的new 的时候会调用operator new
如：
body* a = new body();
这句话等效于如下三个
void* p = operator new(sizeof(body));
p = static_cast(body*)(p);
p->body::body();        //调用构造函数

delete a; 等效于如下两行
a->~body();
operator delete(a);

*/

// 设计一个 重载了operator new和 operator delete的类
class body
{
public:
    body() : h(0) {}
    body(int h) : h(h) {}

    void *operator new(size_t size)
    {
        printf("Through body's operator new!\n");
        return malloc(size);
    }

    void *operator new[](size_t size)
    {
        printf("Through body's operator new[]\n");
        return malloc(size);
    }

    void operator delete(void *f, size_t size)
    {
        printf("through body's operator delete!\n");
        free(f);
    }

    void operator delete[](void *f, size_t size_t)
    {
        printf("Through body's operator delete[]\n");
        free(f);
    }

private:
    int h;
};

void test_overload_operator_new_and_array_new();

int main()
{
    body a;      // 没有经过operator delete 函数
    body &b = a; // 没有经过operator new函数

    body *c = new body(); // 触发operator new函数
    delete c;             // 触发operator delete函数

    body *clist = new body[3];
    delete[] clist;

    test_overload_operator_new_and_array_new();

    return 0;
}

class Foo
{
public:
    int _id;        //4
    long _data;     //8
    string _str;    //8

public:
    static void *operator new(size_t size);
    static void operator delete(void *deadObject, size_t size);
    static void *operator new[](size_t size);
    static void operator delete[](void *deadObject, size_t size);

    Foo() : _id(0) { cout << "default ctor. this=" << this << " id=" << _id << endl; }
    Foo(int i) : _id(i) { cout << "ctor. this=" << this << " id=" << _id << endl; }
    // virtual
    ~Foo() { cout << "dtor. this=" << this << " id=" << _id << endl; }

    // 不加 virtual dtor, sizeof = 12, new Foo[5] => operator new[]() 的 size 參數是 64,
    // 加了 virtual dtor, sizeof = 16, new Foo[5] => operator new[]() 的 size 參數是 84,
    // 上述二例，多出來的 4 可能就是個 size_t 欄位用來放置 array size.
};

void *Foo::operator new(size_t size)
{
    Foo *p = (Foo *)malloc(size);
    cout << "Foo::operator new(), size=" << size << "\t  return: " << p << endl;

    return p;
}

void Foo::operator delete(void *pdead, size_t size)
{
    cout << "Foo::operator delete(), pdead= " << pdead << "  size= " << size << endl;
    free(pdead);
}

void *Foo::operator new[](size_t size)
{
    Foo *p = (Foo *)malloc(size); // crash, 問題可能出在這兒
    cout << "Foo::operator new[](), size=" << size << "\t  return: " << p << endl;

    return p;
}

void Foo::operator delete[](void *pdead, size_t size)
{
    cout << "Foo::operator delete[](), pdead= " << pdead << "  size= " << size << endl;

    free(pdead);
}

//-------------
void test_overload_operator_new_and_array_new()
{
    cout << "\ntest_overload_operator_new_and_array_new().......... \n";

    cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
    cout << "sizeof(string) = "<< sizeof(string) << endl;   //32
    {
        Foo *p = new Foo(7);
        delete p;

        Foo *pArray = new Foo[5]; // 無法給 array elements 以 initializer
        delete[] pArray;
    }

    {
        cout << "testing global expression ::new and ::new[] \n";
        // 這會繞過 overloaded new(), delete(), new[](), delete[]()
        // 但當然 ctor, dtor 都會被正常呼叫.

        Foo *p = ::new Foo(7);  //强制使用全局 operator new函数
        ::delete p;

        Foo *pArray = ::new Foo[5]; //
        ::delete[] pArray;
    }
}