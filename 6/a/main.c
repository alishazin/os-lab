#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int at;
	int bt;
	int ct;
	int tt;
	int wt;
} Process;

Process *ps;

void sortBasedOnAT(int n) {
	
	int i,j,swapped;
	Process temp;

	for (i=0; i<n; i++) {
		swapped = 0;
		for (j=0; j<n-i-1; j++) {
			if (ps[j].at > ps[j+1].at) {
				swapped = 1;
				temp = ps[j];
				ps[j] = ps[j+1];
				ps[j+1] = temp;
			}
		}
		if (!swapped) break;
	}

}

void printTableLine() {
	printf("\n|");
	for (int i=0; i<6; i++) {
		printf("-------|");
	}
}

int main() {

	int i, n;
	float avg_tt = 0;
	float avg_wt = 0;

	printf("Enter total number of processes: ");
	scanf("%d", &n);

	ps = (Process*) malloc(n * sizeof(Process));

	for (i=0; i<n; i++) {
			
		Process p;
		p.pid = i+1;

		printf("Enter arrival time of p%d: ", i+1);
		scanf("%d", &p.at);
		
		printf("Enter burst time of p%d: ", i+1);
		scanf("%d", &p.bt);

		ps[i] = p;
			
	}

	sortBasedOnAT(n);

	printTableLine();
	printf("\n| PID\t| AT\t| BT\t| CT\t| TT\t| WT\t|");
	printTableLine();

	for (i=0; i<n; i++) {
		Process *cur = &ps[i];

		if (i == 0) {
			cur->ct = cur->at + cur->bt;			
		} else {

			Process *prev = &ps[i-1];
			if (cur->at < prev->ct) {
				cur->ct = prev->ct + cur->bt;
			} else {
				cur->ct = cur->at + cur->bt;	
			}
		}
		
		cur->tt = cur->ct - cur->at;
		avg_tt += cur->tt;
		
		cur->wt = cur->tt - cur->bt;
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
