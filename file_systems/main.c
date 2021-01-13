#include <stdio.h>
#include <sys/statvfs.h>
int main()
{
    struct statvfs user;

    if(statvfs(".",&user) == -1)
        perror("error");
    else{
        printf("each block has size of %ld bytes\n", user.f_frsize);
    }

    printf("there are %ld blocks available out of %ld\n", user.f_bavail, user.f_blocks);
    return 0;
}
