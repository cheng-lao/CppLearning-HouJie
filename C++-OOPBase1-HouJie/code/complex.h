#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__


/**
 * 课堂总结
 * 1. 类的变量数据放在 private当中
 * 2. 成员函数的传参尽量传递引用，能加上const需要加上
 * 3. 成员函数的返回值尽量使用引用，只有返回对象是在函数当中创建的时候这个时候不能使用引用返回
 * 4. 初始化的构造函数应该尽量使用 : 后面的方法进行初始化，不要在花括号内初始化
 * 5. 成员函数尽量使用const 修饰限定
 * 6. (知识点) 相同class 实例化的对象之间 调用方法函数 等同于调用友元函数。
 * 7. 如果 const要限定 整个函数而非传递的参数，那么 const 只能加在成员函数上
 * 8. 拷贝构造函数和拷贝赋值函数 编译器会主动提供一个默认的函数，但是不能满足深拷贝，所以一旦有指针的类就必须自己实现深拷贝
 * 
 */


//模块1 对于类和函数的提前声明
class complex; 
complex&
  __doapl (complex* ths, const complex& r);
complex&
  __doami (complex* ths, const complex& r);
complex&
  __doaml (complex* ths, const complex& r);

//模块2 对于类的本体的定义
class complex
{
public:
  complex (double r = 0, double i = 0): re (r), im (i) { }  
  // complex (double r = 0, double i = 0){ re = r; im = i; }  //尽量不要这么写 因为效率不高 并且赋值操作不是在初始化阶段!
  complex& operator += (const complex&);    //参数传递尽量都传递引用，这样速度会更加地快! 返回也是尽可能地返回引用.
  complex& operator -= (const complex&);
  complex& operator *= (const complex&);
  complex& operator /= (const complex&);
  double real () const { return re; } // 如果不改变数据 const必须要加入 为了规范和方便 并且不容易出错!
  double imag () const { return im; }
  int func(const complex& param){ return param.im + param.re; } //这样写能成立 是因为 相同class实例化的各个结果互为Friend
private:
  double re, im;

  friend complex& __doapl (complex *, const complex&);
  friend complex& __doami (complex *, const complex&);
  friend complex& __doaml (complex *, const complex&);
};

//模块3 对于类的内部函数定义的外部实现 以及友元函数的实现
inline complex&
__doapl (complex* ths, const complex& r)
{
  ths->re += r.re;
  ths->im += r.im;
  return *ths;
}
 
inline complex&
complex::operator += (const complex& r)
{
  return __doapl (this, r);
}

inline complex&
__doami (complex* ths, const complex& r)
{
  ths->re -= r.re;
  ths->im -= r.im;
  return *ths;
}
 
inline complex&
complex::operator -= (const complex& r)
{
  return __doami (this, r);
}
 
inline complex&
__doaml (complex* ths, const complex& r)
{
  double f = ths->re * r.re - ths->im * r.im;
  ths->im = ths->re * r.im + ths->im * r.re;
  ths->re = f;
  return *ths;
}

inline complex&
complex::operator *= (const complex& r)
{
  return __doaml (this, r);
}
 
inline double
imag (const complex& x)
{
  return x.imag ();
}

inline double
real (const complex& x)
{
  return x.real ();
}

inline complex
operator + (const complex& x, const complex& y)
{
  return complex (real (x) + real (y), imag (x) + imag (y));
}

inline complex
operator + (const complex& x, double y)
{
  return complex (real (x) + y, imag (x));
}

inline complex
operator + (double x, const complex& y)
{
  return complex (x + real (y), imag (y));
}

inline complex
operator - (const complex& x, const complex& y)
{
  return complex (real (x) - real (y), imag (x) - imag (y));
}

inline complex
operator - (const complex& x, double y)
{
  return complex (real (x) - y, imag (x));
}

inline complex
operator - (double x, const complex& y)
{
  return complex (x - real (y), - imag (y));
}

inline complex
operator * (const complex& x, const complex& y)
{
  return complex (real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}

inline complex
operator * (const complex& x, double y)
{
  return complex (real (x) * y, imag (x) * y);
}

inline complex
operator * (double x, const complex& y)
{
  return complex (x * real (y), x * imag (y));
}

complex
operator / (const complex& x, double y)
{
  return complex (real (x) / y, imag (x) / y);
}

inline complex
operator + (const complex& x)
{
  return x;
}

inline complex
operator - (const complex& x)
{
  return complex (-real (x), -imag (x));
}

inline bool
operator == (const complex& x, const complex& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}

inline bool
operator == (const complex& x, double y)
{
  return real (x) == y && imag (x) == 0;
}

inline bool
operator == (double x, const complex& y)
{
  return x == real (y) && imag (y) == 0;
}

inline bool
operator != (const complex& x, const complex& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}

inline bool
operator != (const complex& x, double y)
{
  return real (x) != y || imag (x) != 0;
}

inline bool
operator != (double x, const complex& y)
{
  return x != real (y) || imag (y) != 0;
}

#include <cmath>

inline complex
polar (double r, double t)
{
  return complex (r * cos (t), r * sin (t));
}

inline complex
conj (const complex& x) 
{
  return complex (real (x), -imag (x));
}

inline double
norm (const complex& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}

#endif   //__MYCOMPLEX__




