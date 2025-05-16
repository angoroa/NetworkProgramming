#include "netprog2.h"
#include <stdio.h>
#include <pthread.h>
#define MAX_THR 2

pthread_t who_run = 0; // prn_data()에서 사용되는 전역변수, 초기값 -1
void prn_data(pthread_t me){
    who_run = me;
    if (who_run != pthread_self())
        printf("Error : %lu 스레드 실행 중 who run = %lu\n", me, who_run);
    else {
       printf("%lu\n", who_run);
   	}
    who_run =0; // 초기값으로 환원
}

void *thrfunc(void *argc){
    while(1) {
        prn_data(pthread_self());
    }
    return NULL;
}


int main(int argc, char **argv){
    pthread_t tid[2];
    int i, status;
    for(i =0; i<MAX_THR; i++){
        if( (status = pthread_create(&tid[i], NULL, &thrfunc, NULL)) !=0){
            printf("thread create error: %s\n", strerror(status));
            exit(0);
        }
    }
    pthread_join(tid[0], NULL);
    return 0;
}

