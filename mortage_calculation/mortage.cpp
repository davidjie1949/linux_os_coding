#include "mortage.h"


mortage::mortage(int year, double interest_rate, double principle, double down_payment)
    : m_year(year), m_interest_rate(interest_rate), m_principle(principle),  m_down_payment(down_payment){}

double mortage::loan_amount(){
    m_loan_amount = m_principle * (1 - m_down_payment);
    return m_loan_amount;
}

double mortage::total_interest_paid(){
    double temp = 0;

    for(int i = 1; i <= 360; i++){
    m_loan_amount = m_loan_amount - temp;
    temp = temp + m_loan_amount * m_interest_rate/12;
    std::cout << temp << " , ";
    }
    return temp;
}
