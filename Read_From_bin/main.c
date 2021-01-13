#include<stdio.h>
#include<stdlib.h>

struct numberThree{
      int num1;
      int num2;
      int num3;
};

int main(){

    int num;
    FILE *fptr;
    struct numberThree number;

    fptr = fopen("exercise.bin", "rb");

    if (fptr == NULL){
        printf("error!");
        exit(1);
    }else{
        for(num = 1; num < 5; ++num){
            fread(&number, sizeof(struct numberThree), 1, fptr);
            printf("num1: %d\tnum2: %d\tnum3: %d\n", number.num1, number.num2, number.num3);
        }
    }

    fclose(fptr);
return 0;
}

/* Our structure */
//struct rec
//{
//    int x,y,z;
//};

//int main()
//{
//    int counter;
//    FILE *ptr_myfile;
//    struct rec my_record;

//    ptr_myfile=fopen("test.bin","rb");
//    if (!ptr_myfile)
//    {
//        printf("Unable to open file!");
//        return 1;
//    }
//    for ( counter=1; counter <= 10; counter++)
//    {
//        fread(&my_record,sizeof(struct rec),1,ptr_myfile);
//        printf("%d\n",my_record.x);
//    }
//    fclose(ptr_myfile);
//    return 0;
//}
