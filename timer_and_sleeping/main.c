#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define INTERVAL 1000 //1000ms

void doSomething(){
    printf("Timer went off.\n");

}

int main(){
    struct itimerval it_val;
    if(signal(SIGALRM, (void(*)(int)) doSomething) == SIG_ERR){
        perror("Unable to catch SIGALRM");
        exit(1);
    }

    it_val.it_value.tv_sec = INTERVAL/1000;
    it_val.it_value.tv_usec = (INTERVAL*1000) % 1000000;

    it_val.it_interval = it_val.it_value;
    if(setitimer(ITIMER_REAL, &it_val, NULL) == -1){
        perror("error calling setitimer()");
        exit(1);
    }

    for (;;)
        pause();
    return 0;
}
