#include<iostream>
using namespace std;
class CDocument
{
public:
    CDocument(){
        cout<<"CDocument::Constructor"<<endl;
    }
    void OnfileOpen(){
        printf("this is %p\n", this);
        cout<<"dialog...."<<endl;
        cout<<"open file..."<<endl;
        this->Serialize();
        cout<<"data display"<<endl;
    }
private:
    virtual void Serialize(){
        cout<<"CDocument::Serialize()"<<endl;
    }
};
class Component
{
public:
/* 先输出CDocument::Constructor, 然后再输出Component::Constructor 
    所以是先进行父类的构造然后是复合关系的成员变量的构造*/
    Component(){
        cout << "Component::Constructor" << endl;
    }
};
class MyDoc: public CDocument{
    Component a;
public:
    // 如果重写了方法，那么在父类调用这个函数会转向调用子类的Serialize函数
    virtual void Serialize() override {
        cout<<"MyDoc::Serialize()"<<endl;
    }
};
int main(){
    MyDoc mdoc;
    printf("mydoc is in %p\n", &mdoc);
    mdoc.OnfileOpen();
}