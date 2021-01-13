#include <iostream>
#include "people.h"

using namespace std;

int main(){
//    taas::base jie(100);
//    cout << jie.getage() << endl;

//    taas::people yang(34, "jie yang");
    taas::base *yang = new taas::people(34, "jieYang");


    cout << yang->getage() << endl;
    delete yang;

//    cout << yang.getage() << endl;
//    cout << yang.getname() << endl;
    return 0;
}
