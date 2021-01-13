#ifndef MORTAGE_H
#define MORTAGE_H

#include <iostream>
using namespace std;

class mortage{
public:
    mortage(int year = 1990, double interest_rate = 0.05, double principle = 1000000, double down_payment = 0.2);

    void setInterestRate(double interest_rate){
    m_interest_rate = interest_rate;
    }
    void setYear(int year){
        m_year = year;
    }
    void setDownPayment(double down_payment){
        m_down_payment = down_payment;
    }
    double getInterestRate() const{
        return m_interest_rate;
    }
    double getYear() const{
        return m_year;
    }
    double getDownPayment() const{
        return m_down_payment;
    }

    double loan_amount();

    double total_interest_paid();
    double total_of_360_payments();

private:
    int m_year;
    double m_interest_rate;
    double m_principle;
    double m_loan_amount;
    double m_down_payment;
};

#endif // MORTAGE_H
