#include "vanillaoption.h"

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double N(const double x) {
  double k = 1.0/(1.0 + 0.2316419*x);
  double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

  if (x >= 0.0) {
    return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
  } else {
    return 1.0 - N(-x);
  }
}

VanillaOption::VanillaOption(){

}

VanillaOption::VanillaOption(double K, double r, double T, double S, double sigma)
    : m_K{K}, m_r{r}, m_T{T}, m_S{S}, m_sigma{sigma}{
}

VanillaOption::VanillaOption(const VanillaOption& rhs){
 copy(rhs);
}

VanillaOption& VanillaOption::operator=(const VanillaOption& rhs){
    if(this == &rhs) return *this;
    copy(rhs);
    return *this;
}

VanillaOption::~VanillaOption(){
    cout << "This class is released" << endl;
}

void VanillaOption::copy(const VanillaOption &rhs){
    this->m_K = rhs.m_K;
    this->m_S = rhs.m_K;
    this->m_T = rhs.m_T;
    this->m_r = rhs.m_r;
    this->m_sigma = rhs.m_sigma;
}

double VanillaOption::calc_call_price() const{
    double sigma_sqrt_T = m_sigma * sqrt(m_T);
    double d_1 = (log (m_S/m_K) + (m_r + m_sigma * m_sigma * 0.5) * m_T) / sigma_sqrt_T;

    double d_2 = d_1 - sigma_sqrt_T;
    return m_S * N(d_1) - m_K * exp(-m_r * m_T) * N(d_2);
}

double VanillaOption::calc_put_price() const{
    double sigma_sqrt_T = m_sigma * sqrt(m_T);
    double d_1 = (log (m_S/m_K) + (m_r + m_sigma * m_sigma * 0.5) * m_T) / sigma_sqrt_T;

    double d_2 = d_1 - sigma_sqrt_T;
    return m_K * exp(-m_r * m_T) * N(-d_2) - m_S * N(-d_1);
}

