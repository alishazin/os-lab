#include <stdio.h>

int abs(int value) {
    if (value < 0)
        return -1 * value;
    return value;
}

void FCFS(int arr[], int n, int head) {

    int head_oprs = 0;
    int cur_oprs;

    printf("Seek sequence: \n");
    printf("%d\n", head);

    for (int i=0; i<n; i++) {

        cur_oprs = abs(head - arr[i]);
        head_oprs += cur_oprs;

        head = arr[i];
        printf("%d\n", head);

    }

    printf("\nTotal head operations: %d", head_oprs);

}

int main() {

    int arr[] = { 98,183,37,122,14,124,65,67 };
    int n = sizeof(arr) / sizeof(int);
    int head = 50;

    FCFS(arr, n, head);

    return 0;
}