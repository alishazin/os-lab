#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
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
        printf("Error: fork failed\n"); exit(1);
    } else if (p == 0) {
        a++;
        printf("Child process: %d\n", getpid()); 
        printf("A: value=%d, addr=%u\n", a, &a); 
        printf("B: value=%d, addr=%u\n", b, &b); 

    } else {
        b++;
        printf("Parent process: %d\n", getpid()); 
        printf("A: value=%d, addr=%u\n", a, &a); 
        printf("B: value=%d, addr=%u\n", b, &b);
    }

    return 0;
}
