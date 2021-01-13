#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(){

    int res = mkdir("/home/jie/Desktop/NewFolder", 0777);
    if (res == 0){
        printf("Created directory!");
    }else{
        printf("Failed to create directory!");
    }

    return 0;
}
