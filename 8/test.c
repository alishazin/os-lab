#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*
Left              Right
       0    1    2
    P0 | P1 | P2 |
*/

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

#define LEFTFORK (phnum + N - 1) % N
#define RIGHTFORK (phnum) % N

#define THINKING_TIME 1
#define EATING_TIME 2

// To store states of each philosopher
int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

// Semaphore to make sure that only one philosopher 
// tries to take fork at a time
sem_t mutex;

// Semaphores of all forks
sem_t S[N];

void take_fork(int phnum) {

    sem_wait(&mutex);

    sem_wait(&S[LEFTFORK]);
    printf("Philosopher %d took fork %d (left)\n", phnum, LEFTFORK);

    sleep(0);
    // A value of zero causes the thread to relinquish the remainder of its 
    // time slice to any other thread that is ready to run. If there are no 
    // other threads ready to run, the function returns immediately, and the 
    // thread continues execution.
    // This step is added so that u can see the deadlock
    
    sem_wait(&S[RIGHTFORK]);

    sem_post(&mutex);

    state[phnum] = EATING;  
    printf("Philosopher %d took fork %d (right) and now eating\n", phnum, RIGHTFORK);

}

void put_fork(int phnum) {

    state[phnum] = THINKING;  
    
    sem_post(&S[LEFTFORK]);
    sem_post(&S[RIGHTFORK]);

}

void* philosopher(void* num) {

    int* phnum = num;

    while (1) {

        state[phil[*phnum]] = THINKING;
        printf("Philosopher %d is thinking\n", *phnum);

        // Thinking time
        sleep(THINKING_TIME);

        state[*phnum] = HUNGRY;
        printf("Philosopher %d is hungry\n", *phnum);

        take_fork(*phnum);

        // Eating time
        sleep(EATING_TIME);

        put_fork(*phnum);

    }

}

int main() {

    int i;
    pthread_t thread[N];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 1);

    for (i = 0; i < N; i++) {
        // create philosopher thread
        pthread_create(&thread[i], NULL, philosopher, &phil[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread[i], NULL);

    return 0;
}