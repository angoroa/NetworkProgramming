#include "netprog2.h"
#include <pthread.h>

//자원개수
int resource_count =0;
//자원 소비 함수
void *consumer_func(void *arg);
//자원 생산 함수
void *producer_func(void *arg);

pthread_mutex_t resource_lock
= PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t resource_cond
= PTHREAD_COND_INITIALIZER;

#define NUM_CONSUMER 10

int main(int argc, char *argv[]){
    int i, id[NUM_CONSUMER];
    pthread_t consumer_thread[NUM_CONSUMER], producer_thread;

    for (i=0; i< NUM_CONSUMER; i++){
        id[i] = i;
        pthread_create(&consumer_thread[i], NULL, &consumer_func, &id[i]);
    }
    pthread_create(&producer_thread, NULL, &producer_func, NULL);

    pthread_join(producer_thread, NULL);

    return 0;
}

void *consumer_func(void *arg){
    int trial = 0, success = 0, id = *((int *)arg);
    while(1) {
        pthread_mutex_lock(&resource_lock);
        // 자원이 없으면 기다림, while 주의
        //while (resource_count == 0)
        //pthread_cond_wait(&resource_cond, &resource_lock);
        trial++; // 시도횟수
        if (resource_count > 0){
            resource_count --; // 자원 하나 소비
            success ++; // 처리 횟수
        }
        pthread_mutex_unlock(&resource_lock);
        printf("%2d: trial = %d success = %d\n", id, trial, success);
    }
    return NULL;
}

void *producer_func(void *arg){
    while(1){
        pthread_mutex_lock(&resource_lock);
        resource_count++; // 자원 하나 생산
        //기다리는 thread가 여러 개이므로
        //pthread_cond_broadcast(&count_cond);
        pthread_mutex_unlock(&resource_lock);
    }
    return NULL;
   
