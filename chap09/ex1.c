#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *thrfunc(void *arg){
	while(1){
		printf("스레드 돌고 있어요!\n");
		sleep(1);
	}
	return NULL;
}

int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, thrfunc, NULL);
	printf("main 끝날 준비중\n");
	pthread_join(tid, NULL);
	return 0;
}

