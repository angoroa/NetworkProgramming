// msgrcv.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFSZ 512

// 메시지 구조체 정의
typedef struct _msg {
    long msg_type;
    char msg_text[BUFSZ];
} msg_t;

// 메시지를 큐에서 수신하는 함수
void message_receive(int qid, long type) {
    msg_t rmsg;

    // 메시지 수신 (msg_text만 크기 계산)
    int nbytes = msgrcv(qid, &rmsg, sizeof(rmsg.msg_text), type, 0);
    if (nbytes == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received %d bytes\n", nbytes);
    printf("Type: %ld\n", rmsg.msg_type);
    printf("Message: %s\n", rmsg.msg_text);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <msgkey>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    key_t key = atoi(argv[1]);

    // 메시지 큐 접근
    int qid = msgget(key, IPC_CREAT | 0660);
    if (qid < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // 타입이 3 이하 중에서 가장 작은 타입부터 꺼냄
    message_receive(qid, -3);
    message_receive(qid, -3);
    message_receive(qid, -3);

    // 큐 제거
    msgctl(qid, IPC_RMID, 0);

    return 0;
}

