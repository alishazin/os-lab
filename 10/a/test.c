#include <stdio.h>
#define FRAMES 3

int in(int value, int arr[], int n) {
    for (int i=0; i<n; i++) {
        if (arr[i] == value) 
            return 1;
    }
    return 0;
}

int main() {

    // int stream[] = {4, 1, 2, 4, 5, 4, 1, 2};
    // int stream[] = {7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1};
    int stream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(stream) / sizeof(int);

    int i, j;
    int lastUsedFrame = -1;
    int totalPageFaults = 0;
    int isCurrPageFault;

    int frames[FRAMES];
    for (i=0; i<FRAMES; i++) {
        frames[i] = -1;
    }

    printf("Incoming\t Frame 1\t Frame 2\t Frame 3\n");
    for (i=0; i<n; i++) {

        printf("%d", stream[i]);

        if (in(stream[i], frames, FRAMES)) {
            isCurrPageFault = 0;
        } else {
            isCurrPageFault = 1;
            frames[(lastUsedFrame = (lastUsedFrame + 1) % FRAMES)] = stream[i];
            totalPageFaults++;
            printf("*");
        }
        printf("\t\t ");

        for (j=0; j<FRAMES; j++) {
            if (frames[j] == -1) 
                printf("-\t\t ");
            else
                printf("%d\t\t ", frames[j]);
        }
        printf("\n");

    }

    printf("\nTotal Page Faults: %d", totalPageFaults);

    return 0;
}