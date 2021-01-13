#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(){
    int server_fd, n_socket, v_read;
    struct sockaddr_in address;

    int opt = 1;
    int addr_length = sizeof(address);
    char buffer[1024] = {0};

    char *hey = "Hey I am server";

    //Creating socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        //AF_INET Ipv4, AF_INET6 Ipv6, SOCK_STREAM is UDP connection
        perror("socket failure!\n");
        exit(EXIT_FAILURE);
    }

    //Forcefully attaching socket to the port 8080
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt error\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //Forcefully attaching socket to the port 8080
    if(bind(server_fd,(struct sockaddr *)&address, sizeof(address)) <0){
        perror("bind error\n");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 3) < 0){
        perror("listen error\n");
        exit(EXIT_FAILURE);
    }

    printf("This is Server!\n");

    while(1){
        if((n_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_length)) < 0){
            perror("accept error\n");
            exit(EXIT_FAILURE);
        }

        v_read = read(n_socket, buffer, 1024);
        printf("size of buffer: %s \n", buffer);
        send(n_socket, hey, strlen(hey), 0);
        printf("Hello Message Host sent \n");
    }

    return 0;
}
