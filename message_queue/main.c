#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct message_Tag{
    long msg_type;
    char msg_txt[500];
} Message;

int main(){

    key_t key;
    int msg_id;
    key = ftok("profile", 65);

    msg_id = msgget(key, 0666 | IPC_CREAT);
    Message message;
    message.msg_type = 1;

    printf("Please write date to send: \n");
    fgets(message.msg_txt, 500, stdin);

    msgsnd(msg_id, &message, sizeof(message), 0);

    printf("we have sent: %s \n", message.msg_txt);

    return 0;
}
