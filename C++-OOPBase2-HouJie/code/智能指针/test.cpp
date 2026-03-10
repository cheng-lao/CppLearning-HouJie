#include<memory>
#include <iostream>

using namespace std;
class Parent;
class Child;
class Parent{
private:
    shared_ptr<Child> ChildPtr;
public:
    void setChild(shared_ptr<Child> child){
        ChildPtr = child;
    }
};

class Child{
private:
    shared_ptr<Parent> ParentPtr;
public:
    void setParent(shared_ptr<Parent> parent){
        this->ParentPtr = parent;
    }
};


int main(){
    
    
    return 0;
}