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

    msgrcv(msg_id, &message, sizeof(message), 1, 0);

    printf("This msg or data that we have received is : %s \n", message.msg_txt);
    msgctl(msg_id,IPC_RMID, NULL);

    return 0;
}
