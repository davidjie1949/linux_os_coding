#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>

namespace taas{
class base{
public:
    explicit base(int age);
    virtual ~base();

    void setage(int& age){m_age = age;};
    int getage(){return m_age;};
private:

    int m_age;

};

}

#endif // BASE_H
