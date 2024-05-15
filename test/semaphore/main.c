#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
const int MAX = 1e9;
int ans = 0;

void *myThread(void* args) {

    // To decrement semaphore.
    // When the value of the semaphore is zero, any process that performs a 
    // wait operation will be blocked until another process performs a signal 
    // operation.
    sem_wait(&mutex);
    // Critical Section

    for (int i=0; i<MAX; i++)
        ans++;
    
    printf("Thread %d in critical section with ans: %d\n", *((int*)args), ans);
    ans = 0;

    // END -----------
    sem_post(&mutex);
    // To increment the value of semaphore

}

int main() { 
   
    // To initialize a sempahore
    
    // sem_init(sem_t *sem, int pshared, unsigned int value);

    // sem : Specifies the semaphore to be initialized.
    // pshared : 0 for threads, non-zero for process
    // value : Specifies the value to assign to the newly initialized semaphore.
    
    sem_init(&mutex, 0, 1);

    pthread_t t1,t2,t3;

    int param1 = 1;
    pthread_create(&t1, NULL, myThread, (void *)&param1);
    int param2 = 2;
    pthread_create(&t2, NULL, myThread, (void *)&param2);
    int param3 = 3;
    pthread_create(&t3, NULL, myThread, (void *)&param3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&mutex); 
   
    return 0; 
} 