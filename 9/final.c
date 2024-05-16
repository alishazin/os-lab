#include <stdio.h>
#include <stdlib.h>
#define PROCESS_COUNT 5
#define RESOURCE_COUNT 4

int in(int value, int arr[], int n) {
	for (int i=0; i<n; i++) {
		if (arr[i] == value) return 1;
	}
	return 0;
}

int main() {

	int alloc[PROCESS_COUNT][RESOURCE_COUNT] = {
		{0,0,1,2},
		{1,0,0,0},
		{1,3,5,4},
		{0,6,3,2},
		{0,0,1,4}
	};

	int max[PROCESS_COUNT][RESOURCE_COUNT] = {
		{0,0,1,2},
		{1,7,5,0},
		{2,3,5,6},
		{0,6,5,2},
		{0,6,5,6}
	};

	int avail[RESOURCE_COUNT] = {1,5,2,0};

	int need[PROCESS_COUNT][RESOURCE_COUNT];

	int safe[PROCESS_COUNT];
	int count=0;

	int i,j;

	for (i=0; i<PROCESS_COUNT; i++) {
		for (j=0; j<RESOURCE_COUNT; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	while (1) {
	
		int added_to_safe = 0;

		for (i=0; i<PROCESS_COUNT; i++) {
			
			if (in(i+1, safe, count)) continue;

			int available = 0;

			for (j=0; j<RESOURCE_COUNT; j++) {
				if (need[i][j] <= avail[j]) available++;
			}

			if (available == RESOURCE_COUNT) {
				for (j=0; j<RESOURCE_COUNT; j++) {
					avail[j] += alloc[i][j];
				}

				safe[count] = i+1;
				count++;
				added_to_safe=1;
			}

		}

		if (!added_to_safe) break;

	}

	if (count == PROCESS_COUNT) {
		printf("Safe sequence is: ");
		for (i=0; i<count-1; i++) printf("P%d -> ", safe[i]);
		printf("P%d\n", safe[count - 1]);
	} else {
		printf("System is not safe!\n");
	}

	return 0;
}
