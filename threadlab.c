/*
 *Lyn Quintana
 *PID: 5381212
 * I affirm that I wrote this program myself without any help from anyother people
 * or sources on the internet
 * */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8
int shared;
pthread_mutex_t lock_x;
typedef struct thread{
	int tid;
} thread;
void *sharedID(void *arg){
	thread *data=(thread *)arg;
	for(int i=0; i<10;i++){
		shared+=data->tid;
	}
	printf("Thread [%d] has finished.\n", data->tid);
}
int main(){
	shared=0;
	int id;
	pthread_t tid[NUM_THREADS];
	thread thr[NUM_THREADS];
	pthread_mutex_init(&lock_x, NULL);
	for(int i=0; i<NUM_THREADS; i++){
		thr[i].tid=i;
		if((id=pthread_create(&tid[i], NULL, sharedID, &thr[i]))){
			printf("error\n");
		}
	}
	pthread_mutex_lock(&lock_x);
	for(int i=0; i<NUM_THREADS; i++){
		pthread_join(tid[i], NULL);
	}
	pthread_mutex_unlock(&lock_x);
	printf("Shared: %d\n", shared);
	return 0;
}
