#include <stdio.h>

int main(void) {
    int pid[5] = {1, 2, 3, 4, 5};
    int at[5]  = {0, 1, 2, 3, 4};
    int bt[5]  = {6, 8, 7, 3, 4};
    int ct[5] = {0}, tat[5] = {0}, wt[5] = {0}, done[5] = {0};
    int order[5], start[5];
    int n = 5, time = 0, completed = 0;
    double avg_wt = 0, avg_tat = 0;

    while (completed < n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        order[completed] = shortest;
        start[completed] = time;
        time += bt[shortest];
        ct[shortest] = time;
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];
        avg_wt += wt[shortest];
        avg_tat += tat[shortest];
        done[shortest] = 1;
        completed++;
    }

    printf("Non-Preemptive SJF Scheduling\n\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nGantt Chart\n");
    for (int i = 0; i < n; i++) printf("| P%d ", pid[order[i]]);
    puts("|");
    for (int i = 0; i < n; i++) printf("%-7d", start[i]);
    printf("%d\n", ct[order[n - 1]]);

    printf("\nAverage Waiting Time    : %.2f\n", avg_wt / n);
    printf("Average Turnaround Time : %.2f\n", avg_tat / n);
    return 0;
}
