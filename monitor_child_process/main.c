#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    pid_t cpid;
    if(fork() == 0){
        printf("Hello World!\n");
        exit(0);
     }else{
        cpid = wait(NULL);
    }

    printf("Parent process id (pid): %d\n", getpid());
    printf("Child process id (pid): %d\n", cpid);
    return 0;
}
