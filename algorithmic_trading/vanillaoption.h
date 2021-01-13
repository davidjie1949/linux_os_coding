#ifndef VANILLAOPTION_H
#define VANILLAOPTION_H
#include <cmath>
#include <iostream>

using namespace std;

/* @brief
 * @param K,
 * @param r,
 */

class VanillaOption{
public:
    VanillaOption();
    VanillaOption(double K = 100.0, double r = 0.05, double T = 1.0, double S = 100, double sigma = 0.2);
    VanillaOption(const VanillaOption& rhs); //copy constructor
    VanillaOption& operator=(const VanillaOption& rhs); //assignment operator

    virtual ~VanillaOption();

    void setK(double K){m_K = K;}
    void setr(double r){m_r = r;}
    void setT(double T){m_T = T;}
    void setS(double S){m_S = S;}
    void setSigma(double Sigma){ m_sigma = Sigma;}

    double getK() const {return m_K;}
    double getr() const {return m_r;}
    double getT() const {return m_T;}
    double getS() const {return m_S;}
    double getSigma() const {return m_sigma;}

    double calc_call_price() const;
    double calc_put_price() const;

private:

    void copy(const VanillaOption& rhs);
    double m_K;
    double m_r;
    double m_T;
    double m_S;
    double m_sigma;
};

#endif // VANILLAOPTION_H
