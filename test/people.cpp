#include "people.h"

taas::people::people(int age, std::string name) : base(age), m_name(name){
    std::cout << "people class created!" << std::endl;
}

taas::people::~people(){
    std::cout << "people class deleted!" << std::endl;
}
