#include <stdio.h>
#define DISK_SIZE 200 
// from 0 to DISK_SIZE - 1 cylinders

int abs(int value) {
    if (value < 0)
        return -1 * value;
    return value;
}

int sortRequestsAndSeparate(int* arr, int n, int head) {
    int i,j,swapped,temp;
    for (i=0; i<n-1; i++) {
        swapped = 0;
        for (j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
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

void SCAN(int arr[], int n, int head, int toLeft) {

    int head_oprs = 0;
    int run = 0;
    int cur_oprs;
    int current_end;

    int firstAfterHead = sortRequestsAndSeparate(arr, n, head);

    printf("Seek sequence: \n");

    while (1) {
        if (toLeft) {

            for (int i=firstAfterHead-1; i >= 0; i--) {
                cur_oprs = abs(head - arr[i]);
                head_oprs += cur_oprs;

                head = arr[i];
                printf("%d\n", head);
            }

            if (run == 1) break;

            current_end = 0;
            toLeft = 0;

        } else {

            for (int i=firstAfterHead; i < n; i++) {
                cur_oprs = abs(head - arr[i]);
                head_oprs += cur_oprs;

                head = arr[i];
                printf("%d\n", head);
            }

            if (run == 1) break;

            current_end = DISK_SIZE-1;
            toLeft = 1;

        }

        cur_oprs = abs(head - current_end);
        head_oprs += cur_oprs;
        head = current_end;
        printf("%d\n", head);

        run++;
    }

    printf("\nTotal head operations: %d", head_oprs);

}

int main() {

    int arr[] = { 178, 79, 34, 60, 92, 11, 39, 114 };
    int n = sizeof(arr) / sizeof(int);
    int head = 50;
    int toLeft = 1; // 1 if moving to left, 0 if moving to right 

    SCAN(arr, n, head, toLeft);

    return 0;
}