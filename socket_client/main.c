#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define INADDR "127.0.0.1"

int main(){
    int sock_1, v_read;
    struct sockaddr_in address;

    char buffer[1024] = {0};
    char *hey = "Hey I am client!";

    if ((sock_1 = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failure\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, INADDR, &address.sin_addr) <= 0){
        perror("Invalid IP address");
        return -1;
    }

    printf("This is client!\n");

    while(1){
        if(connect(sock_1, (struct sockaddr*)&address, sizeof(address)) < 0){
            perror("connection failure");
            return -1;
        }

        send(sock_1, hey, strlen(hey), 0);
        printf("Hello Message Client sent \n");
        v_read = read(sock_1, buffer, 1024);
        printf("size of buffer: %s \n", buffer);
    }

    return 0;
}
