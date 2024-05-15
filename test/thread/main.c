#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *retval;

pthread_t thread_id;
pthread_t thread_id2;

void *myThread(void *vargp) {
    sleep(1);
    printf("In Thread\n");

    pthread_exit(retval);
    // retval must be global, and this method exists the current thread

    printf("Self Id: %d\n", pthread_self());
    return NULL;
}

void *threadWithParam(void *vargp) {

    sleep(1);
    printf("Param: %d\n", *((int*)vargp));

    // pthread_equal()
    // if equal => returns non-zero
    // if not equal => returns zero
    printf("Equal check return: %d\n", pthread_equal(pthread_self(), thread_id2));
    printf("Equal check return: %d\n", pthread_equal(pthread_self(), thread_id));
    return NULL;

}

int main() {

    printf("Before Thread\n");
    
    pthread_create(&thread_id, NULL, myThread, NULL);
    // Or this works for both
    // pthread_detach(pthread_create(&thread_id, NULL, myThread, NULL));
    
    // To start and wait for the thread to end
    // pthread_join(thread_id, NULL);

    // To start the thread
    // pthread_detach(thread_id);
    // sleep(2); // so that the main thread wont end before the sub thread

    // To pass param to a thread
    int param = 10;
    pthread_create(&thread_id2, NULL, threadWithParam, (void *)&param);
    pthread_join(thread_id2, NULL);

    printf("After Thread\n");

    return 0;
}