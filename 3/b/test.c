#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	
	int p1,p2,p3;
	
	p1 = fork();
	p2 = fork();

	printf("Hello %d %d %ld\n", p1, p2, getpid());

	return 0;
}
