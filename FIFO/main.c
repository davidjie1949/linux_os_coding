#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(){
    char fn[] = "linuxTemp.fifo";
    char out[40] = "this is FIFO and this is linux", in[100];
    int rf, wf;

    if(mkfifo(fn,S_IRWXU) != 0){
        perror("mkfifo fault");
    }else{
        if((rf = open(fn, O_RDONLY | O_NONBLOCK)) < 0)
            perror("open fault");
        else{
            if (write(wf, out, strlen(out) + 1) == -1)
                perror("write fault");
            else if(read(rf, in, sizeof(in)) == -1)
                perror("read fault!");
            else{
                printf("reading '%s' from FIFO \n", in);
            }
            close(wf);
        }
        close(rf);
    }

    unlink(fn);

    printf("Hello World!\n");
    return 0;
}
