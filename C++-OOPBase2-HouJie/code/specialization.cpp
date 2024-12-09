// Encoding: UTF-8
#include<cstdio>
#include<iostream>
using namespace std;

template<class key>
struct specialization { 
    
};

template<>
struct specialization<char>
{
    char operator() (char p){ return p;}
};
//模板特化，对于泛化的某些特殊类型进行特殊针对，所以对这些类型单独写一份特殊的处理逻辑
//书写方式其实就是先加上一个 template<> 然后再写struct

int main(){
    cout << specialization<char>()('c');
}


