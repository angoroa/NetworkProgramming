// msgsnd.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFSZ 512

// 메시지 구조체 정의
typedef struct _msg {
    long msg_type;               // 메시지 타입 (반드시 양수)
    char msg_text[BUFSZ];        // 메시지 내용
} msg_t;

// 메시지를 큐에 전송하는 함수
void message_send(int qid, long type, const char* text) {
    msg_t pmsg;
    pmsg.msg_type = type;

    int len = strlen(text);
    strncpy(pmsg.msg_text, text, len);
    pmsg.msg_text[len] = '\0';  // 문자열 종료 보장

    // 메시지 전송
    if (msgsnd(qid, &pmsg, len, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <msgkey>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    key_t key = atoi(argv[1]);

    // 메시지 큐 생성 또는 접근 (0660 권한)
    int qid = msgget(key, IPC_CREAT | 0660);
    if (qid < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    char text[BUFSZ];

    puts("Enter message to post: ");
    fgets(text, BUFSZ, stdin);

