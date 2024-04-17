#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
// only for non-preemptive
Process *processes;

Block *blocks;
int b_size = 0;

Node *queue;
int q_size = 0;

int main() {

    int n;
    int i;
    int cur_time = 0;
    float avg_tt = 0;
    float avg_wt = 0;

    printf("Enter the number of processes you want to create: ");
    scanf("%d", &n);

    processes = (Process*) malloc(n * sizeof(Process));
    queue = (Node*) malloc(n * sizeof(Node));
    blocks = (Block*) malloc(10 * sizeof(Block));

    for (i=0; i<n; i++) {
        Process process;

        printf("\nEnter the Arrival Time of P%d: ", i + 1);
        scanf("%d", &process.arrival_time);

        printf("\nEnter the Burst Time of P%d: ", i + 1);
        scanf("%d", &process.burst_time);

        process.q_pushed_flag = 0;
        processes[i] = process;
    }

    while (1) {
        int all_pushed_flag = 1;
        for (i=0; i<n; i++) {
            if (processes[i].q_pushed_flag == 0) {
                all_pushed_flag = 0;
                if (processes[i].arrival_time <= cur_time) {
                    push(queue, &q_size, i+1, processes[i].burst_time);
                    processes[i].q_pushed_flag = 1;
                }
            }   
        }

        if (q_size != 0) {
            Node node = pop(queue, &q_size);
            processes[node.pid - 1].completion_time = cur_time + processes[node.pid - 1].burst_time;
            processes[node.pid - 1].turnaround_time = processes[node.pid - 1].completion_time - processes[node.pid - 1].arrival_time;                                                                                                                 
            processes[node.pid - 1].waiting_time = processes[node.pid - 1].turnaround_time - processes[node.pid - 1].burst_time;                                                                                                                      
            
            Block block;
            block.start = cur_time;
            cur_time += processes[node.pid - 1].burst_time;
            block.end = cur_time;
            block.pid = node.pid;
            blocks[b_size] = block;
            b_size++;
        } else {
            cur_time++;                                                                                     
        }

        if (all_pushed_flag == 1 && q_size == 0) break;
    }

    printTable(processes, &avg_tt, &avg_wt, n);
    printGantt(b_size, blocks);
    printAvgTTWT(avg_tt, avg_wt, n);

    return 0;

}