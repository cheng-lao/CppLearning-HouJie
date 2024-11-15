#include<cstring>

class MyString
{
private:
    char* m_data;   //
public:
    MyString(const char* cstr = 0);
    MyString(const MyString& str);
    MyString& operator=(const MyString& str);
    ~MyString();
    char* get_c_str() const { return m_data; }
};

inline
MyString::MyString( const char* cstr = 0 )
{
    if(cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else{
        m_data = new char[1];   //和析构函数对应,适用数组delete;
        *m_data = '\0';
    }
}

inline
MyString::~MyString()
{
    delete[] m_data;
}

MyString::MyString(const MyString& str){
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

inline
MyString& MyString::operator=(const MyString& str){
    
    if(this == &str)
        return *this;

    delete[] m_data;
    m_data = new char[ strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}