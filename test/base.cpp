#include "base.h"

taas::base::base(int age) : m_age(age){
    std::cout << " base class created! " << std::endl;
}

taas::base::~base(){
    std::cout << "base class deleted! " << std::endl;
}

