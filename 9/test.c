#include <stdio.h>
#define PROCESS_COUNT 5
#define RESOURCE_COUNT 4

int in_operator(int value, int arr[], int arr_length) {

    for (int i=0; i<arr_length; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;

}

int main() {

    int alloc[PROCESS_COUNT][RESOURCE_COUNT] = {
        { 0, 0, 1, 2 },
        { 1, 0, 0, 0 },
        { 1, 3, 5, 4 },
        { 0, 6, 3, 2 },
        { 0, 0, 1, 4 }
    };

    int max[PROCESS_COUNT][RESOURCE_COUNT] = { 
        { 0, 0, 1, 2 },
        { 1, 7, 5, 0 }, 
        { 2, 3, 5, 6 }, 
        { 0, 6, 5, 2 }, 
        { 0, 6, 5, 6 }
    };

    int avail[RESOURCE_COUNT] = {1, 5, 2, 0};

    int need[PROCESS_COUNT][RESOURCE_COUNT]; 

    int safe_sequence_count = 0;
    int safe_sequence[PROCESS_COUNT];

    // Computing Need Matrix
    for (int i=0; i<PROCESS_COUNT; i++) {
        for (int j=0; j<RESOURCE_COUNT; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    while (1) {

        int added_to_safe = 0;

        for (int i=0; i<PROCESS_COUNT; i++) {

            if (in_operator(i+1, safe_sequence, safe_sequence_count))
                continue;

            int available = 0;

            for (int j=0; j<RESOURCE_COUNT; j++) {
                if (avail[j] >= need[i][j]) {
                    available++;
                }
            }

            if (available == RESOURCE_COUNT) {
                for (int j=0; j<RESOURCE_COUNT; j++) {
                    avail[j] += alloc[i][j];
                }
                
                safe_sequence[safe_sequence_count++] = i+1;
                added_to_safe = 1;
            }

        }

        if (!added_to_safe) break;

    }

    if (safe_sequence_count != PROCESS_COUNT) {
        printf("The following system is not safe");
    } else {
        printf("Following is the SAFE sequence:\n");
        for (int i = 0; i < safe_sequence_count-1; i++) {
            printf("P%d -> ", safe_sequence[i]);
        }
        printf("P%d", safe_sequence[safe_sequence_count-1]);
    }

    return 0;
}