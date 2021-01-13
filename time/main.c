#include <stdio.h>
#include <time.h>

void function_time(){
    printf("function starts \n");
    printf("Press enter key to exit \n");
    for(;;){
        if(getchar()){
            break;
        }
    }
    printf("function ends \n");
}

int main(){

    clock_t t = clock();
    function_time();
    t = clock() - t;

    double time_taken_by_function = ((double)t)/CLOCKS_PER_SEC;

    printf("here is process time: %f", time_taken_by_function);

    return 0;
}
