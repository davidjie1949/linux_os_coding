#ifndef DERIVED_H
#define DERIVED_H
#include "base.h"

class derived : public base{
public:
    derived(int highth, double length, double width);

    void highth(int highth){
        m_highth = highth;
    }

    int highth(){
        return m_highth;
    }

    double area();

private:
    int m_highth;
};

#endif // DERIVED_H
