#include <pthread.h>
#include "netprog2.h"
void *thrfunc(void *arg); // 스레드 시작 함수 원형
char who[10];
int main(int argc, char *argv[]){
    int status;
    pthread_t tid;
    pid_t pid;
    if((pid = fork()) == 0 )sprintf(who, "child"); //자식 프로세스 생성
    else sprintf(who, "parent");

    printf("(%s's main) Process ID = %d\n", who, getpid()); // 프로세스 ID와 초>기 스레드의 ID 확인
    printf("(%s's main) Init thread ID = %lu\n", who, pthread_self());

    status = pthread_create(&tid, NULL, &thrfunc, NULL);

    if (status !=0){
        printf("thread create error: %s\n", strerror(status));
        exit(0);
    }

    pthread_join(tid, NULL); // 인자로 지정한 스레드가 종료하기를 기다림
    printf("\n(%s) [%lu] 스레드가 종료했습니다\n", who, tid);
    return 0;


}
void *thrfunc(void *arg){
    printf("(%s' thread routine) Process ID = %d\n", who, getpid());
    printf("(%s' thread routine) Thread ID = %lu\n", who, pthread_self());
}

