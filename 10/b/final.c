#include <stdio.h>
#include <stdlib.h>
#define FRAMES 3

typedef struct {
	int value;
	int lastUpdated;
} frame;

int in(int value, frame arr[]) {
	for (int i=0; i<FRAMES; i++) {
		if (arr[i].value == value) return i;
	}
	return -1;
}

int getLRU(frame arr[]) {
	int minV = arr[0].lastUpdated;
	int minI = 0;
	for (int i=1; i<FRAMES; i++) {
		if (arr[i].lastUpdated < minV) {
			minV = arr[i].lastUpdated;
			minI = i;
		}	
	}
	return minI;
}

int main() {

	int stream[] = {1,2,3,1,2,4,5};
	int n = sizeof(stream) / sizeof(stream[0]);

	int i,j;
	int totalPF = 0;

	frame frames[FRAMES];
	for (i=0; i<FRAMES; i++) {
		frame f;
		f.value = -1;
		frames[i] = f;
	}

	printf("Incoming\t Frame 1\t Frame 2\t Frame 3\n");
	for (i=0; i<n; i++) {
	
		int frameIndex = in(stream[i], frames);

		printf("%d", stream[i]);
		if (frameIndex != -1) {
			frames[frameIndex].lastUpdated = i;
		} else {

			if (i < FRAMES) {
				frames[i].value = stream[i];
				frames[i].lastUpdated = i;
			} else {
				int LRU = getLRU(frames);
				frames[LRU].value = stream[i];
				frames[LRU].lastUpdated = i;
			}
			totalPF++;
			printf("*");
		}

		printf("\t\t ");

		for (j=0; j<FRAMES; j++) {
			if (frames[j].value == -1) printf("-\t\t ");
			else printf("%d\t\t ", frames[j].value);
		}
		printf("\n");

	}

	printf("Total page faults: %d\n", totalPF);

	return 0;
}
