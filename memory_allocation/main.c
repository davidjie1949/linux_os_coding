#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, sum = 0;

    num = 8;
//    int *ptr = (int*)malloc(num*sizeof(int));
    int *ptr = (int*)calloc(num, sizeof(int));
    ptr = realloc(ptr, 16*sizeof(int));
    printf("Memory has been re-allocated!");
    if(ptr == NULL){
        printf("Memory Allocation Failed!");
        exit(1);
    }else{
        printf("Memory Allocation Succeeded!");
    }
    printf("We have %d elements to allocate memory to:", num);

    for (int i = 0; i < num; i++){
        ptr[i] = i + 1;
    }

    printf("inserted 8 elements in the block are as follows:\n");
    for (int i = 0; i < num; i++){
        printf("%d, ", ptr[i]);
    }

    free(ptr);
    return 0;
}
