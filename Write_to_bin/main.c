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

    fptr = fopen("exercise.bin", "wb");

    if (fptr == NULL){
        printf("error!");
        exit(1);
    }else{
        for(num = 1; num < 5; ++num){
            number.num1 = num;
            number.num2 = 2*num;
            number.num3 = 2*num + 3;
            fwrite(&number, sizeof(struct numberThree), 1, fptr);
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

//    ptr_myfile=fopen("test.bin","wb");
//    if (!ptr_myfile)
//    {
//        printf("Unable to open file!");
//        return 1;
//    }
//    for ( counter=1; counter <= 10; counter++)
//    {
//        my_record.x= counter;
//        fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
//    }
//    fclose(ptr_myfile);
//    return 0;
//}
