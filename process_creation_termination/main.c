#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
    fork(); //create new process to run the following code
    for(int i = 0;; i++){
        printf("Linux Hello! %d\n", i);
    }
    return 0;
}
