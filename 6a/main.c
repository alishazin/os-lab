#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

Process *processes;

int sortBasedOnArrivalTime(int n) {
    int swapped;
    int i,j;
    Process temp;

    for (int i=0; i<n-1; i++) {
        swapped = 0;
        for (int j=0; j<n-i-1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0) break;
    }
}

int main() {

    int n;
    int blocks = 0;
    float avg_tt = 0;
    float avg_wt = 0;

    printf("Enter the number of processes you want to create: ");
    scanf("%d", &n);

    processes = (Process*) malloc(n * sizeof(Process));

    for (int i=0; i<n; i++) {
        Process process;
        process.pid = i + 1;
        
        printf("\nEnter the Arrival Time of P%d: ", i + 1);
        scanf("%d", &process.arrival_time);

        printf("\nEnter the Burst Time of P%d: ", i + 1);
        scanf("%d", &process.burst_time);

        processes[i] = process;
    }

    sortBasedOnArrivalTime(n);

    // Printing Table

    printf("\n|-------|-------|-------|-------|-------|-------|");
    printf("\n| PID\t| AT\t| BT\t| CT\t| TT\t| WT\t|");
    printf("\n|-------|-------|-------|-------|-------|-------|");
    
    for (int i=0; i<n; i++) {
        
        if (i == 0) {
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
        } else {
            if (processes[i].arrival_time < processes[i - 1].completion_time) {
                processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
            } else {
                processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
            }
        }
        
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        avg_tt += processes[i].turnaround_time;

        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        avg_wt += processes[i].waiting_time;
        
        printf("\n| P%d\t| %d\t| %d\t| %d\t| %d\t| %d\t|", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\n|-------|-------|-------|-------|-------|-------|\n\n0\t");

    // Printing Gantt Chart

    for (int i=0; i<n; i++) {
        if (i == 0 && processes[i].arrival_time != 0) {
            printf("%d\t", processes[i].arrival_time);
            blocks++;
        } else if (processes[i-1].completion_time < processes[i].arrival_time) {
            printf("%d\t", processes[i].arrival_time);
            blocks++;
        }
        printf("%d\t", processes[i].completion_time);
        blocks++;
    }

    printf("\n");
    for (int i=0; i<blocks; i++) printf("|-------");
    printf("|\n");

    for (int i=0; i<n; i++) {
        if (i == 0 && processes[i].arrival_time != 0) {
            printf("| IDLE\t");
        } else if (processes[i-1].completion_time < processes[i].arrival_time) {
            printf("| IDLE\t");
        }
        printf("| P%d\t", processes[i].pid);
    }

    printf("|\n");
    for (int i=0; i<blocks; i++) printf("|-------");
    printf("|\n");

    avg_tt = avg_tt / n;
    avg_wt = avg_wt / n;

    printf("\nAverage Turnaround Time: %.2f", avg_tt);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    return 0;
}