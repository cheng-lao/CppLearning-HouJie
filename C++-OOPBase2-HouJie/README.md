+ 视频直达：[C++ 面向对象高级编程下-兼谈对象模型](https://www.bilibili.com/video/BV1ZX4y157Bu)
+ 课程讲义下载直达：[slide](slide/)
+ 源代码直达：[code](code/)

----

候捷老师 C++ 系列课程导航：（编号顺序可作为学习顺序参考）

1. [C++面向对象高级编程（上）-基于对象和面向对象](../C++-OOPBase1-HouJie/)
2. C++面向对象高级编程（下）-兼谈对象模型
3. [C++标准库(STL)与泛型编程](../C++-STL-HouJie/)
4. [C++新标准-C++11/14](../C++-newC++11&14-HouJie/)
5. [C++内存管理](../C++-MemoryManagement-HouJie/)
6. [C++Startup揭秘](https://github.com/19PDP/Bilibili-plus)



---

## 课程简介

这是侯捷老师的所有C++技术课程中最基础最根本的一门课。

C++可说是第一个高度普及的Object-Oriented（面向对象）程序语言。“第一个”
或“最早的”并非重点，重点是经过多年的淬炼和考验C++的影响深入各层面，
拥有众多使用者和极其丰富的资源（书籍、论文、期刊、视频、第三方程序库…）。

作为Object-Oriented（面向对象）技术的主流语言，C++其实还拥有另一支编程
主线：模板与泛型编程（Templates and Generic Programming）。

本课程涵盖上述两条主线：Object-Oriented（面向对象）和泛型编程（Generic
Programming）。

由于视频录制时程的因素，本课程分为Part I和Part II.
Part I主要讨论OO（面向对象）的基础概念和编程手法。基础最是重要，勿在浮
沙筑高台，着重的是大器与大气。课程首先探讨Class without pointer members
和Class with pointer members两大类型，而后晋升至OOP/OOD，包括classes之
间最重要的三种关系：继承（Inheritance）、复合（Composition）、委托（Delegation）。
Part II继续探讨更多相关主题，并加上低阶的对象模型（Object Model），以及高
阶的Templates（模板）编程。

本课程所谈主题都隶属C++1.0（C++98）；至于C++ 2.0（C++11/14）带来的崭新
内容则由侯捷老师的 [另一门课程](../C++-newC++11&14-HouJie) 涵盖。C++2.0在语言和标准库两方面都带来了很多新
事物，份量足以形成另一门课程。

你将获得整个video课程的完整讲义（也就是video呈现的每一张投影片画面），
和完整的示例程序。你可以（也有必要）在学习过程中随时停下来思考和阅读讲义。

> 侯捷简介：程序员，软件工程师，台湾工研院副研究员，教授，专栏主笔。曾任
> 教于中坜元智大学、上海同济大学、南京大学。著有《无责任书评》三卷、《深
> 入浅出MFC》、《STL源码剖析》…，译有《Effective C++》《More Effective C++》
> 《C++ Primer》《The C++ Standard Library》…



---

以下这份不太细致的主题划分，帮助您认识整个课程内容。

## C++面向對象編程 (C++Object-Oriented Programming)

### Part I

**Introduction of C++98, TR1, C++11, C++14**<br>
&emsp;Bibliography<br>
&emsp;Data and Functions, from C to C++<br>
&emsp;Basic forms of C++ programs<br>
&emsp;About output<br>
&emsp;Guard declarations of header files<br>
&emsp;Layout of headers<br>
&emsp;Object Based<br>
&emsp;Class without pointer member<br>
&emsp;&emsp;Class declarations<br>
&emsp;&emsp;Class template, introductions and overviews<br>
&emsp;&emsp;What is 'this'<br>
&emsp;&emsp;Inline functions<br>
&emsp;&emsp;Access levels<br>
&emsp;&emsp;Constructor (ctor)<br>
&emsp;&emsp;Const member functions<br>
&emsp;&emsp;Parameters : pass by value vs. pass by reference<br>
&emsp;&emsp;Return values : return by value vs. return by reference<br>
&emsp;&emsp;Friend<br>
&emsp;&emsp;Definitions outside class body<br>
&emsp;&emsp;Operator overloading, as member function<br>
&emsp;&emsp;Return by reference, again<br>
&emsp;&emsp;Operator overloading, as non-member function<br>
&emsp;&emsp;Temporary objects<br>
&emsp;&emsp;Expertise<br>
&emsp;&emsp;Code demonstration<br>
&emsp;class with pointer members<br>
&emsp;&emsp;The "Big Three"<br>
&emsp;&emsp;&emsp;Copy Constructor<br>
&emsp;&emsp;&emsp;Copy Assignment Operator<br>
&emsp;&emsp;&emsp;Destructor<br>
&emsp;&emsp;Ctor and Dtor, in our String class<br>
&emsp;&emsp;"MUST HAVE" in our String class<br>
&emsp;&emsp;&emsp;Copy Constructor<br>
&emsp;&emsp;&emsp;Copy assignment operator<br>
&emsp;&emsp;Deal with "self assignment"<br>
&emsp;&emsp;Another way to deal with "self assignment" : Copy and Swap<br>
&emsp;&emsp;Overloading output operator (<<)<br>
&emsp;&emsp;Expertise<br>
&emsp;&emsp;Code demonstration<br>
&emsp;Objects from stack vs. objects from heap<br>
&emsp;&emsp;Objects lifetime<br>
&emsp;&emsp;new expression : allocate memory and then invoke ctor<br>
&emsp;&emsp;delete expression : invoke dtor and then free memory<br>
&emsp;&emsp;Anatomy of memory blocks from heap<br>
&emsp;&emsp;Allocate an array dynamically<br>
&emsp;&emsp;new[] and delete[]<br>
&emsp;MORE ISSUES :<br>
&emsp;&emsp;static<br>
&emsp;&emsp;private ctors<br>
&emsp;&emsp;cout<br>
&emsp;&emsp;Class template<br>
&emsp;&emsp;Function template<br>
&emsp;&emsp;namespace<br>
&emsp;&emsp;Standard Library : Introductions and Overviews<br>
&emsp;Object Oriented<br>
&emsp;&emsp;Composition means "has-a"<br>
&emsp;&emsp;&emsp;Construction : from inside to outside<br>
&emsp;&emsp;&emsp;Destruction : from outside to inside<br>
&emsp;&emsp;Delegation means "Composition by reference"<br>
&emsp;&emsp;Inheritance means "is-a"<br>
&emsp;&emsp;&emsp;Construction : from inside to outside<br>
&emsp;&emsp;&emsp;Destruction : from outside to inside<br>
&emsp;&emsp;Construction and Destruction, when Inheritance+Composition<br>
&emsp;&emsp;Inheritance with virtual functions<br>
&emsp;&emsp;Virtual functions typical usage 1 : Template Method<br>
&emsp;&emsp;Virtual functions typical usage 2 : Polymorphism<br>
&emsp;&emsp;Virtual functions inside out : vptr, vtbl, and dynamic binding<br>
&emsp;&emsp;Delegation + Inheritance : Observer<br>
&emsp;&emsp;Delegation + Inheritance : Composite<br>
&emsp;&emsp;Delegation + Inheritance : Prototype<br>

### Part II

**绪论**<br>
Conversion function（转换函数）<br>
Non-explicit one-argument constructor<br>
Pointer-like classes，关于智能指针<br>
Pointer-like classes，关于迭代器<br>
Function-like classes，所谓仿函数<br>
标准库中的仿函数的奇特模样<br>
namespace经验谈<br>
class template，类模板<br>
function template，函数模板<br>
member template，成员模板<br>
specialization，模板特化<br>
partial specialization，模板偏特化——个数的偏<br>
partial specialization，模板偏特化——范围的偏<br>
```cpp
//偏特化分为两种：个数的偏特化和范围的偏特化
//偏特化是指对模板中的某些参数进行特化，而不是对所有参数进行特化
//特化主要是在泛化的过程当中会有一些特殊情况，特化就是为解决这些特殊情况而出现的。
#include<iostream>
using namespace std;

//完全特化
template<class key>
struct specialization { 
    
};

template<>
struct specialization<char>
{
    char operator() (char p){ return p;}
};

//偏特化与完全特化不同，完全特化是为特定类型提供完全不同的实现，而偏特化则是为一部分类型提供不同的实现。
//范围的偏特化，对原先的所有类型到 用一个指针指向某个类型
template<typename T>
struct C{   //原先的泛化是一个元素
    // ...  
};
template<typename T>
struct C<T*>{   //这里限定到指针，也可以是const 等等
    // ...
};

//数量上的偏特化, 语法如下
//针对到某个typename 需要改变，但是另一个可以不用改变
template<typename T,typename Alloc=/*....*/>
struct vector{
    // ...  
};

template<typename Alloc=/**/>
struct vector<bool, Alloc>{
    //...
}

```
template template parameter，模板模板参数<br>

~~这个好难www~~
```cpp
//写法类似如下

//第一种写法----Encoder: UTF-8
#include<iostream>
#include<vector>
using namespace std;

template<class T, template<typename U1, typename U2> 
               class Container>// 这里其实限定了传进来的第二个类型必须是模板，并且模板所需要的参数只能有两个
class Xcls{
private:
    Container<T, std::allocator<T>> c;
public:
    Xcls(): c(Container<T, std::allocator<T>>()) {  }
};
int main()
{
    Xcls<char, vector> pv; 
    cout <<"Compile Success" << endl;
    return 0;
}

//第二种写法----Encoder:UTF-8
//
template<class T, template<typename U1> 
               class Container> // 第二个参数必须是一个模板类
class Xcls{
private:
    Container<T> c;
public:
    Xcls(): c(Container<T>()) {  }
};

template<typename T>
class A { };

int main()
{
    // Xcls<char, vector> pv; //类模板 "std::vector" 与 模板 template 参数 "Container" 不兼容
    Xcls<char, A> pa;
    //自己实现模板类的可以编译，但是STL标准模板库当中就不行!
    cout <<"Compile Success" << endl;
    return 0;
}


// 最后看一个 不是模板模板参数的例子
// 模板模板参数的关键是一个类的模板参数 也是一个模板，
// 但是在下面stack当中 第二个类型参数传递进来的时候，其实已经确定了类型是什么了，是一个确定的类型参数，而不是模板参数。
// 所以不是模板
template <class T, class Sequence = deque<T>>
class stack{
    friend bool operator== <> (const stack&, const stack&);
    friend bool operator< <> (const stack&, const stack&);
    
protected:
    Sequence c;
}

```

variadic templates（since C++11）<br>
auto（since C++11）<br>
ranged-base for（since C++11）<br>
reference<br>
Composition（复合）关系下的构造和析构<br>
Inheritance（继承）关系下的构造和析构<br>
Inheritance+Composition关系下的构造和析构<br>
对象模型（Object Model）：关于vptr和vtbl<br>
对象模型（Object Model）：关于this<br>
对象模型（Object Model）：关于Dynamic Binding<br>
谈谈const<br>
关于new，delete<br>
重载 ::operator new，::operator delete<br>
重载 ::operator new[]，::operator delete[]<br>
重载 member operator new/delete<br>
重载 member operator new[]/delete[]<br>
示例<br>
重载new()，delete()<br>
示例<br>
basic_string使用new（extra）扩充申请量

-- the end

