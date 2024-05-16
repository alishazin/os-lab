#include <stdio.h>
#include <stdlib.h>

int abs(int value) {
	if (value < 0) return -1 * value;
	return value;
}

void FCFS(int req[], int n, int head) {

	int i;
	int totalHO = 0;
	int curHO;

	printf("Seek sequence:\n%d\n", head);

	for (i=0; i<n; i++) {
		curHO = abs(head - req[i]);
		totalHO += curHO;
		head = req[i];

		printf("%d\n", head);
	}

	printf("Total head movements: %d\n", totalHO);

};

int main() {
	
	int req[] = {98, 183,37,122,14,124,65,67};
	int n = sizeof(req)/sizeof(req[0]);
	int head = 50;

	FCFS(req, n, head);;

	return 0;
}
