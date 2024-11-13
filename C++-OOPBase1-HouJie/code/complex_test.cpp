#include <iostream>
#include "complex.h"

using namespace std;

ostream&  //这里的假如说 是 cout << c1 << c2，先执行的是左边的'<<'然后是再执行右边的 '<<' ,所以为了保持左边的对象类型一致性需要返回ostream&
operator << (ostream& os, const complex& x)
{
  return os << '(' << real (x) << ',' << imag (x) << ')';
}

int main()
{
  complex c1(2, 1);
  complex c2(4, 0);

  cout << c1 << endl;
  cout << c2 << endl;
  
  cout << c1+c2 << endl;
  cout << c1-c2 << endl;
  cout << c1*c2 << endl;
  cout << c1 / 2 << endl;
  
  cout << conj(c1) << endl;
  cout << norm(c1) << endl;
  cout << polar(10,4) << endl;
  
  cout << (c1 += c2) << endl;
  
  cout << (c1 == c2) << endl;
  cout << (c1 != c2) << endl;
  cout << +c2 << endl;
  cout << -c2 << endl;
  
  cout << (c2 - 2) << endl;
  cout << (5 + c2) << endl;
  
  return 0;
}
