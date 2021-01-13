#include <stdio.h>
#include <unistd.h>
int main()
{

    int processID, parent_processID_1,parent_processID_2;
    processID = getpid();
    parent_processID_1 = getppid();
    parent_processID_2 = getppid();

    while(1){
    printf("process_id = %d\n", processID);
    printf("parent processID = %d\n", parent_processID_1);
    printf("parent processID = %d\n", parent_processID_2);
    }
    return 0;
}
