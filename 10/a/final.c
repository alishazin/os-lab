#include <stdio.h>
#include <stdlib.h>
#define FRAMES 3

int in(int value, int arr[], int n) {
	for (int i=0; i<n; i++) {
		if (arr[i] == value) return 1;
	} 
	return 0;
}

int main() {

	int stream[] = {1,2,3,2,4,5,2};
	int n = sizeof(stream) / sizeof(stream[0]);

	int i,j;
	int totalPF = 0;
	int lastUsedFrame = -1;

	int frames[FRAMES];
	for (i=0; i<FRAMES; i++) frames[i] = -1;

	printf("Incoming\t Frame 1\t Frame 2\t Frame 3\n");
	for (i=0; i<n; i++) {

		printf("%d", stream[i]);
	
		if (!in(stream[i], frames, FRAMES)) {
			totalPF++;
			printf("*");

			frames[(lastUsedFrame = (lastUsedFrame + 1) % FRAMES)] = stream[i];
		}
		printf("\t\t ");

		for (j=0; j<FRAMES; j++) {
			if (frames[j] == -1) printf("-\t\t ");
			else printf("%d\t\t ", frames[j]);
		}
		printf("\n");

	}

	printf("Total page faults: %d\n", totalPF);

	return 0;

}
