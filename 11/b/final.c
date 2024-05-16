#include <stdio.h>
#include <stdlib.h>
#define DISKSIZE 200

int abs(int value) {
	if (value < 0) return -1 * value;
	return value;
}

int sortReqAndSeparate(int *arr, int n, int head) {
	int i,j,temp,swapped;
	for (i=0; i<n; i++) {
		swapped = 0;
		for (j=0; j<n-i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				swapped = 1;
			}
		}
		if (!swapped) break;
	}

	for (i=0; i<n; i++) {
		if (arr[i] > head) break;
	}
	return i;
}

void update(int *totalHO, int *head, int cur) {
	*totalHO += abs(*head - cur);
	*head = cur;
	printf("%d\n", *head);
}

void SCAN(int req[], int n, int head, int toLeft) {

	int i;
	int totalHO = 0;
	int run = 0;
	int cur_end;

	int FAH = sortReqAndSeparate(req, n, head);

	printf("Seek sequence: \n%d\n", head);

	while (1) {
	
		if (toLeft) {
		
			for (i=FAH-1; i>=0; i--) {
				update(&totalHO, &head, req[i]);
			}

			if (run == 1) break;

			toLeft = 0;
			cur_end = 0;

		} else {
		
			for (i=FAH; i<n; i++) {
				update(&totalHO, &head, req[i]);
			}

			if (run == 1) break;

			toLeft = 1;
			cur_end = DISKSIZE - 1;

		}

		update(&totalHO, &head, cur_end);

		run++;
	}

	printf("Total head movements: %d\n", totalHO);

}

int main() {

	int req[] = {178,79,34,60,92,11,39,114};
	int n = sizeof(req) / sizeof(req[0]);
	int head = 50;
	int toLeft = 1;

	SCAN(req, n, head, toLeft);

	return 0;
}
