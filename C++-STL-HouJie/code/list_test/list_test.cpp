#include<iostream>
#include<list>

using namespace std;

int main(){

    list<int> lint;
    for(int i = 10;i < 20; i++)
        lint.push_back(i);
    int i=1;
    for(auto it = lint.begin(); it != lint.end(); i++ ,it++){
        cout<<"i: "<< i <<" elem: "<< *it << endl;
    }
    
    cout<<"begin == end ? answer: "<< (lint.begin() == lint.end() ? "true" : "false") << endl;
    cout<<"data same? begin == end ? answer: "<< (*lint.begin() == *lint.end() ? "true" : "false") << endl;

    return 0;
}