#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

int main() {

    printf("Before fork\n");
    int a = 10; // variable before fork 
    a++;

    int p = fork();
    
    int b = 10; // variable after fork
    b++;

    printf("After fork\n");

    if (p < 0) {
        printf("Error: fork failed\n"); 
        exit(1);
    } else if (p == 0) {
       	b++;
        a++;
        printf("Child process: %ld\n", getpid());
        printf("A: value=%d\n", a);
        printf("B: value=%d\n", b);
    } else {
        b++;
        printf("Parent process: %ld\n", getpid()); 
        printf("A: value=%d\n", a);
        printf("B: value=%d\n", b);
    }

    return 0;
}
