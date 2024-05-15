#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

const int MAX = 1e9;
int available = 1;
int ans = 0;
pthread_mutex_t lock;

void* myThread(void *vargs) {

    pthread_mutex_lock(&lock); 
    // Critical Section
    
    for (int i=0; i<MAX; i++)
        ans++;
    
    printf("Thread %d in critical section with ans: %d\n", *((int*)vargs), ans);
    ans = 0;
    
    // END -----------
    pthread_mutex_unlock(&lock); 

    return NULL;

}

int main() {

    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;

    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }

    int param1 = 1;
    pthread_create(&thread_id1, NULL, myThread, (void *)&param1);
    int param2 = 2;
    pthread_create(&thread_id2, NULL, myThread, (void *)&param2);
    int param3 = 3;
    pthread_create(&thread_id3, NULL, myThread, (void *)&param3);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    pthread_mutex_destroy(&lock); 

    return 0;
}