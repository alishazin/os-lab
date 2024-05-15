#include <stdio.h>
#define FRAMES 3

typedef struct {
    int value;
    int lastUpdated;
} frame;

int in(int value, frame arr[], int n) {
    for (int i=0; i<n; i++) {
        if (arr[i].value == value) 
            return i;
    }
    return -1;
}

int getLeastRecentlyUpdated(frame arr[], int n) {
    int min = arr[0].lastUpdated;
    int minIndex = 0;
    for (int i=1; i<n; i++) {
        if (arr[i].lastUpdated < min) {
            min = arr[i].lastUpdated;
            minIndex = i;
        }
    }
    return minIndex;
}

int main() {

    int stream[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int n = sizeof(stream) / sizeof(int);

    int i, j;
    int totalPageFaults = 0;
    int isCurrPageFault;

    frame frames[FRAMES];
    for (i=0; i<FRAMES; i++) {
        frames[i].value = -1;
    }

    printf("Incoming\t Frame 1\t Frame 2\t Frame 3\n");
    for (i=0; i<n; i++) {

        printf("%d", stream[i]);

        int frameIndex = in(stream[i], frames, FRAMES);

        if (frameIndex != -1) {
            isCurrPageFault = 0;
            frames[frameIndex].lastUpdated = i;
        } else {
            isCurrPageFault = 1;

            if (i < FRAMES) {
                frames[i].value = stream[i];
                frames[i].lastUpdated = i;
            } else {
                int LRUIndex = getLeastRecentlyUpdated(frames, FRAMES);
                frames[LRUIndex].value = stream[i];
                frames[LRUIndex].lastUpdated = i;
            }
            totalPageFaults++;
            printf("*");

        }
        printf("\t\t ");

        for (j=0; j<FRAMES; j++) {
            if (frames[j].value == -1) 
                printf("-\t\t ");
            else
                printf("%d\t\t ", frames[j]);
        }
        printf("\n");

    }

    printf("\nTotal Page Faults: %d", totalPageFaults);

    return 0;
}