#include <iostream>
#include <sys/time.h>
using namespace std;
void test(int &a, int &b){
    a--;
    b--;
    if(a >= 0){
    cout << a << " " << b << endl;
    test(a, b);
    }
}

int main(){
    timeval v1, v2;
    gettimeofday(&v1, NULL);

    cout << v1.tv_sec << " " << v1.tv_usec << endl;

    int test1 = 9000;
    int test2 = 9000;
    test(test1,test2);

    gettimeofday(&v2, NULL);

    cout << v2.tv_sec << " " << v2.tv_usec << endl;

    cout << (double)(v2.tv_usec - v1.tv_usec)/100000 + (double)(v2.tv_sec - v1.tv_sec);

    return 0;
}
