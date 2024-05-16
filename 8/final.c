#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 3
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define THINKING_TIME 2
#define EATING_TIME 1

#define LEFTFORK (phnum + N - 1) % N
#define RIGHTFORK phnum

int state[N];
int phil[N] = {0,1,2};

sem_t wrap;
sem_t S[N];

void take_fork(int phnum) {

	sem_wait(&wrap);

	sem_wait(&S[LEFTFORK]);
	printf("Philosopher %d took fork %d (left)\n", phil[phnum], LEFTFORK);

	sleep(0);

	sem_wait(&S[RIGHTFORK]);
	
	sem_post(&wrap);

	state[phnum] = EATING;
	printf("Philosopher %d took fork %d (right) and started eating\n", phil[phnum], RIGHTFORK);

}

void put_fork(int phnum) {
	sem_post(&S[LEFTFORK]);
	sem_post(&S[RIGHTFORK]);
}

void *philosopher(void* num) {

	int phnum = *((int*) num);

	while (1) {
	
		state[phnum] = THINKING;
		printf("Philosopher %d is thinking\n", phil[phnum]);

		sleep(THINKING_TIME);

		state[phnum] = HUNGRY;
		printf("Philosopher %d is hungry\n", phil[phnum]);

		take_fork(phnum);

		sleep(EATING_TIME);

		put_fork(phnum);

	}

}

int main() {

	int i;
	pthread_t threads[N];

	sem_init(&wrap, 0, 1);

	for (i=0; i<N; i++) {
		sem_init(&S[i], 0, 1);
	}

	for (i=0; i<N; i++) {
		pthread_create(&threads[i], NULL, philosopher, (void*) &phil[i]);
	}

	for (i=0; i<N; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}

