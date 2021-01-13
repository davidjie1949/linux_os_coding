#include <iostream>
#include "mortage.h"

using namespace std;

int main(){

    mortage jieYang(2020, 0.02375, 600000, 0.2);
    cout << jieYang.getYear() << endl;
    cout << jieYang.getDownPayment() << endl;
    cout << jieYang.getInterestRate() << endl;
    cout << jieYang.loan_amount() << endl;
    cout << jieYang.total_interest_paid() << endl;
    return 0;
}
