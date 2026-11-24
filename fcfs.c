#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt;
};

int main(void) {
    struct Process p[5] = {
        {1, 2, 6, 0, 0, 0},
        {2, 0, 4, 0, 0, 0},
        {3, 1, 8, 0, 0, 0},
        {4, 4, 3, 0, 0, 0},
        {5, 3, 5, 0, 0, 0}
    };
    int n = 5, time = 0;
    double avg_wt = 0, avg_tat = 0;

    /* Sort by arrival time (FCFS order). */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("FCFS Scheduling\n\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nGantt Chart\n");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        printf("| P%d ", p[i].pid);
        time += p[i].bt;
    }
    printf("|\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        printf("\t%d", time);
    }
    printf("\n\nAverage Waiting Time    : %.2f\n", avg_wt / n);
    printf("Average Turnaround Time : %.2f\n", avg_tat / n);
    return 0;
}
