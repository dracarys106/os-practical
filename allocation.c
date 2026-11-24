#include <stdio.h>

#define NB 5
#define NP 4

enum Strategy { FIRST_FIT, BEST_FIT, WORST_FIT };

void allocate(const int blocks[], const int processes[], enum Strategy strategy) {
    int remaining[NB], allocation[NP];

    for (int i = 0; i < NB; i++) remaining[i] = blocks[i];
    for (int i = 0; i < NP; i++) allocation[i] = -1;

    for (int i = 0; i < NP; i++) {
        int chosen = -1;

        for (int j = 0; j < NB; j++) {
            if (remaining[j] < processes[i]) continue;

            if (strategy == FIRST_FIT) {
                chosen = j;
                break;
            } else if (chosen == -1 ||
                       (strategy == BEST_FIT && remaining[j] < remaining[chosen]) ||
                       (strategy == WORST_FIT && remaining[j] > remaining[chosen])) {
                chosen = j;
            }
        }

        if (chosen != -1) {
            allocation[i] = chosen;
            remaining[chosen] -= processes[i];
        }
    }

    const char *title = strategy == FIRST_FIT ? "First Fit" :
                        strategy == BEST_FIT ? "Best Fit" : "Worst Fit";
    printf("\n%s\n", title);
    printf("Process\tSize\tBlock\tRemaining\n");

    for (int i = 0; i < NP; i++) {
        if (allocation[i] == -1)
            printf("P%d\t%d\tNot Allocated\n", i + 1, processes[i]);
        else
            printf("P%d\t%d\t%d\t%d\n", i + 1, processes[i],
                   allocation[i] + 1, remaining[allocation[i]]);
    }
}

int main(void) {
    int blocks[NB] = {100, 500, 200, 300, 600};
    int processes[NP] = {212, 417, 112, 426};

    printf("Memory Blocks: ");
    for (int i = 0; i < NB; i++) printf("%d ", blocks[i]);
    printf("\nProcesses: ");
    for (int i = 0; i < NP; i++) printf("%d ", processes[i]);
    puts("");

    allocate(blocks, processes, FIRST_FIT);
    allocate(blocks, processes, BEST_FIT);
    allocate(blocks, processes, WORST_FIT);
    return 0;
}
