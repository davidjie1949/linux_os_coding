#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void hello(){
    while(1){
    cout<<"Hello Concurrent World\n" << endl;
    }
}
int  main(){
    pid_t getpid(void);
    cout << "pid: " << getpid() << endl;
    pid_t pid = fork();

    if (pid == 0){
        hello();
        cout << "pid: "<< pid << endl;
    }else{
        while(1){
        cout << "jie Yang" << endl;
        cout <<"pid: " << pid << endl;
        }
    }
    return 0;
}
