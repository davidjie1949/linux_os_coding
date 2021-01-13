#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    (void)argv;
    struct flock flk = {F_WRLCK, SEEK_SET, 0, 0, 0};
    int fd;
    flk.l_pid = getpid();

    if (argc > 1)
        flk.l_type = F_RDLCK;
    if((fd = open("main.c", O_RDWR)) == -1){
        perror("Error to opening file");
        exit(0);
    }

    printf("Hit Enter to lock the file \n");
    getchar();

    printf("Checking if we could lock the file or not \n");
    if(fcntl(fd, F_SETLKW, &flk) == -1){
        perror("fcntl error!");
        exit(0);
    }
    printf("Lock Success!\n");

    printf("Hit Enter to unlock the file \n");
    getchar();
    flk.l_type = F_UNLCK;

    if(fcntl(fd, F_SETLK, &flk) == -1){
        perror("fcntl error!");
        exit(0);
    }






    return 0;
}
