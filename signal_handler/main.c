#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signalHandler(int temp){
    printf("Caught signal %d, I am going to exit.\n", temp);
    exit(1);
}

int main()
{
    signal(SIGINT, signalHandler);

    for (;;){
        printf("Sleeping...\n");
        sleep(3);
    }
    return 0;
}
