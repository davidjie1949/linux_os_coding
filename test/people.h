#ifndef PEOPLE_H
#define PEOPLE_H
#include "base.h"
namespace taas{

class people : virtual public base {
public:
    people(int age, std::string name);
    virtual ~people();

    void setname(std::string& name){m_name = name;};
    std::string getname(){return m_name;};

private:
    std::string m_name;
};
}
#endif // PEOPLE_H
