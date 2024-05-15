#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int at;
	int bt;
	int ct;
	int tt;
	int wt;
	int pushed;
	int rbt;
} Process; 

Process *ps;
Process *cur_p = NULL;

void printTableLine() {
	printf("\n|");
	for (int i=0; i<6; i++) printf("-------|");
}

int main() {

	int n,i,preemptive;

	printf("Enter 0 for non-preemtive and 1 for preemptive: ");
	scanf("%d", &preemptive);
	
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	ps = (Process*) malloc(n * sizeof(Process));

	for (i=0; i<n; i++) {
		
		Process p;
		p.pid = i+1;

		printf("Enter the arrival time of P%d: ", i+1);
		scanf("%d", &p.at);
		
		printf("Enter the burst time of P%d: ", i+1);
		scanf("%d", &p.bt);

		p.rbt = p.bt;
		p.pushed = 0;

		ps[i] = p;

	}

	int cur_time = 0;
	int completed_count = 0;
	int pushed_count = 0;
	float avg_tt=0;
	float avg_wt=0;

	while (1) {
		// Decrement rbt and calculate ct,tt,wt if completed	
		if (cur_p != NULL) {
			cur_p->rbt -= 1;
			if (cur_p->rbt == 0) {
				cur_p->ct = cur_time;
				cur_p->tt = cur_p->ct - cur_p->at;
				cur_p->wt = cur_p->tt - cur_p->bt;
				cur_p->pushed = 0;
				cur_p = NULL;
				completed_count++;
			}
		}

		// find shortest unfinished process
		Process *short_p = NULL;
		for (i=0; i<n; i++) {
			if (ps[i].rbt == 0) continue;
			if (ps[i].pushed == 0) {
				if (ps[i].at == cur_time) {
					ps[i].pushed = 1;
					pushed_count++;
				}
			}
			
			if (ps[i].pushed == 1 && (short_p == NULL || ps[i].rbt < short_p->rbt)) {
				short_p = &ps[i];
			}

		}
		
		// do preemption or add new process if empty
		if (pushed_count) {
			
			if (cur_p == NULL) {
				cur_p = short_p;
				short_p->pushed = 0;
				pushed_count--;
			} else if (preemptive && short_p->rbt <= cur_p->rbt) {
				cur_p->pushed = 1;
				cur_p = short_p;
				short_p->pushed = 0;
			}

		}

		if (pushed_count == 0 && completed_count == n && cur_p == NULL) break;

		cur_time++;
	}

	printTableLine();
        printf("\n| PID\t| AT\t| BT\t| CT\t| TT\t| WT\t|");
        printTableLine();	

	for (i=0; i<n; i++) {
                Process *cur = &ps[i];

		avg_tt += cur->tt;
                avg_wt += cur->wt;

                printf("\n| P%d\t| %d\t| %d\t| %d\t| %d\t| %d\t|", cur->pid, cur->at, cur->bt, cur->ct, cur->tt, cur->wt);
	}
	printTableLine();printf("\n");

        avg_tt /= n;
        avg_wt /= n;

        printf("\nAvg Turnaround Time: %0.2f", avg_tt);
        printf("\nAvg Waiting Time: %0.2f\n", avg_wt);

	return 0;
}
