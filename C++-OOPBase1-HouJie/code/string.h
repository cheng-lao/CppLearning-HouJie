#ifndef __MYSTRING__
#define __MYSTRING__

/**
 * 关于new String发生的事情
 * String *ps = new String("Hello"); 实际发生的是下面的三行
 * void* mem = operator new( sizeof(String) )
 * ps = static_cast<String*>(mem);
 * ps->String:String("Hello");
 * 
 * 关于delete String 发生的事情
 * deltete ps; 实际发生的事情是下面的两行
 * String:~String(ps);        //释放class内部定义的指针 m_data
 * operator delete(ps);       //释放ps指针指向的内存 delete内部调用了free(ps) 
 * 
 * 
 * 
 */


class String
{
public:                                 
   String(const char* cstr=0);                     
   String(const String& str);                    
   String& operator=(const String& str);         
   ~String();                                    
   char* get_c_str() const { return m_data; }
private:
   char* m_data;
};

#include <cstring>

inline
String::String(const char* cstr)
{
   if (cstr) {
      m_data = new char[strlen(cstr)+1];
      strcpy(m_data, cstr);
   }
   else {   
      m_data = new char[1];
      *m_data = '\0';
   }
}

inline
String::~String()
{
   delete[] m_data;
}

inline
String& String::operator=(const String& str)
{
   if (this == &str) //检测是否是自我赋值!
      return *this;

   delete[] m_data;
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
   return *this;
}

inline
String::String(const String& str)
{
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
}

#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const String& str)
{
   os << str.get_c_str();
   return os;
}

#endif
