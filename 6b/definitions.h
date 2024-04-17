
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int q_pushed_flag;
} Process;

typedef struct {
    int start;
    int end;
    int pid;
} Block;

typedef struct {
    int pid;
    int burst_time;
} Node;

Node pop(Node *queue, int* q_size) {
    int i;
    int min = 0;
    for (i=1; i<*q_size; i++) {
        if (queue[i].burst_time < queue[min].burst_time) {
            min = i;
        }
    }
    Node returnValue = queue[min];
    for (i=min; i<*q_size; i++) {
        queue[i] = queue[i + 1];
    }
    (*q_size)--;
    return returnValue;
}

Node push(Node *queue, int* q_size, int pid, int remaining_burst_time) {
    Node node;
    node.pid = pid;
    node.burst_time = remaining_burst_time;
    queue[*q_size] = node;
    (*q_size)++;
}

void printGantt(int b_size, Block *blocks) {

    int idle_blocks = 0;
    int i;

    for (i=0; i<b_size; i++) {
        if (i == 0 && blocks[i].start != 0) {
            printf("%d\t", blocks[i].start);
            idle_blocks++;
        } else if (i != 0) {
            if (blocks[i].start != blocks[i-1].end) {
                printf("%d\t", blocks[i-1].end);
                idle_blocks++;
            }
            printf("%d\t", blocks[i].start);
        }
        if (i == b_size - 1) {
            printf("%d\t", blocks[i].end);
        }
    }

    printf("\n");
    for (int i=0; i<b_size + idle_blocks; i++) printf("|-------");
    printf("|\n");

    for (i=0; i<b_size; i++) {
        if (i == 0 && blocks[i].start != 0) {
            printf("| IDLE\t");
        } else if (i != 0 && blocks[i].start != blocks[i-1].end) {
            printf("| IDLE\t");
        } 
        printf("| P%d\t", blocks[i].pid);
    }

    printf("|\n");
    for (int i=0; i<b_size + idle_blocks; i++) printf("|-------");
    printf("|\n");

}

Block createBlock(Block* blocks, int* b_size, int start, int end, int pid) {
    Block block;
    block.start = start;
    block.end = end;
    block.pid = pid;
    blocks[*b_size] = block;
    (*b_size)++;
    return block;
}

void printTable(Process *processes, float *avg_tt, float *avg_wt, int n) {
    printf("\n|-------|-------|-------|-------|-------|-------|");
    printf("\n| PID\t| AT\t| BT\t| CT\t| TT\t| WT\t|");
    printf("\n|-------|-------|-------|-------|-------|-------|");

    for (int i=0; i<n; i++) {
        *avg_tt += processes[i].turnaround_time;
        *avg_wt += processes[i].waiting_time;
        printf("\n| P%d\t| %d\t| %d\t| %d\t| %d\t| %d\t|", i + 1, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\n|-------|-------|-------|-------|-------|-------|\n\n0\t");
}

void printAvgTTWT(float avg_tt, float avg_wt, int n) {
    avg_tt = avg_tt / n;
    avg_wt = avg_wt / n;

    printf("\nAverage Turnaround Time: %.2f", avg_tt);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
}