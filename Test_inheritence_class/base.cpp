#include "base.h"

base::base(double length, double width)
    : m_length{length}, m_width{width}{

}

double base::tringle(){
    double temp;
    temp = m_length * m_width;
    return temp;
}

base::~base(){

}
