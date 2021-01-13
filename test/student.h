#ifndef STUDENT_H
#define STUDENT_H
#include "people.h"

namespace taas{

class student : virtual public people{
public:
    student(int age, std::string name, int grade);
    virtual ~student();
private:
    int m_scores;
};
}
#endif // STUDENT_H
