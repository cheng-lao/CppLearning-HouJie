//encoding: UTF-8
#include<iostream>

using namespace std;

double imag(const double& im){
    cout<<"reference "<<im<<endl;
}
double imag(const double im) 
{
    cout<<"value "<<im<<endl;
}

int main(){

    // imag(3.14);
    int b = 10;
    int& a = b;
    int c = 100;
    a = c;  //不能再变化引用的对象了，所以这里是单纯的赋值
    cout<<"a is "<<a<<" b is "<<b<<" c is "<<c<<endl;


    return 0;
}
