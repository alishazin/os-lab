#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

int main() {

    Process *processes;
    Block *blocks;
    int b_size = 0;
    Node *queue;
    int q_size = 0;
    Process *cur_process = NULL;

    int n;
    int i;
    int preemptive;
    int cur_time = 0;
    float avg_tt = 0;
    float avg_wt = 0;

    printf("Enter 0 for non-preemptive and 1 for preemptive : ");
    scanf("%d", &preemptive);

    printf("Enter the number of processes you want to create: ");
    scanf("%d", &n);

    processes = (Process*) malloc(n * sizeof(Process));
    queue = (Node*) malloc(n * sizeof(Node));
    blocks = (Block*) malloc(50 * sizeof(Block));

    for (i=0; i<n; i++) {
        Process process;

        printf("\nEnter the Arrival Time of P%d: ", i + 1);
        scanf("%d", &process.arrival_time);

        printf("\nEnter the Burst Time of P%d: ", i + 1);
        scanf("%d", &process.burst_time);

        process.remaining_burst_time = process.burst_time;
        process.q_pushed_flag = 0;
        process.pid = i + 1;
        processes[i] = process;
    }

    while (1) {
        
        if (cur_process != NULL) {
            cur_process->remaining_burst_time -= 1;   
            if (cur_process->remaining_burst_time == 0) {
                cur_process->completion_time = cur_time;
                cur_process->turnaround_time = cur_process->completion_time - cur_process->arrival_time;
                cur_process->waiting_time = cur_process->turnaround_time - cur_process->burst_time;
                cur_process = NULL;
                blocks[b_size - 1].end = cur_time;
            }
        }

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

            if (cur_process == NULL) {
                Block block = createBlock(blocks, &b_size, cur_time, -1, node.pid);
                cur_process = &processes[node.pid - 1];
            } else if (preemptive == 1 && cur_process != NULL && node.burst_time <= cur_process->remaining_burst_time) {
                push(queue, &q_size, cur_process->pid, cur_process->remaining_burst_time);

                if (blocks[b_size - 1].end == -1) {
                    blocks[b_size - 1].end = cur_time;
                }

                Block block = createBlock(blocks, &b_size, cur_time, -1, node.pid);
                cur_process = &processes[node.pid - 1];
            } else if (cur_process != NULL) {
                push(queue, &q_size, node.pid, node.burst_time);
            }

        }

        if (all_pushed_flag == 1 && q_size == 0 && cur_process == NULL) break;
        cur_time++;
    }

    printTable(processes, &avg_tt, &avg_wt, n);
    printGantt(b_size, blocks);
    printAvgTTWT(avg_tt, avg_wt, n);

    return 0;

}