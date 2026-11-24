#include <stdio.h>
#include <string.h>

#define MAX_PROC 5
#define MEM_SIZE 1024
#define QUANTUM 3

struct pcb {
    int pid;
    char name[16];
    int remaining;
    int mem_start;
    int mem_size;
    char state[12];
};

struct pcb table[MAX_PROC];
int count = 0, next_free = 0;

void create_process(const char *name, int burst, int mem) {
    if (count >= MAX_PROC) {
        printf("Process %s: process table is full\n", name);
        return;
    }
    if (next_free + mem > MEM_SIZE) {
        printf("Process %s: memory allocation failed\n", name);
        return;
    }

    struct pcb *p = &table[count];
    p->pid = 100 + count;
    strcpy(p->name, name);
    p->remaining = burst;
    p->mem_size = mem;
    p->mem_start = next_free;
    next_free += mem;
    strcpy(p->state, "READY");

    printf("Created PID=%d NAME=%-8s MEMORY=[%d - %d]\n",
           p->pid, p->name, p->mem_start, p->mem_start + mem - 1);
    count++;
}

void show_table(void) {
    printf("\n%-6s %-10s %-12s %-10s %-10s\n",
           "PID", "NAME", "STATE", "REMAINING", "MEM SIZE");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-10s %-12s %-10d %-10d\n",
               table[i].pid, table[i].name, table[i].state,
               table[i].remaining, table[i].mem_size);
    }
}

void round_robin(void) {
    int time = 0, done = 0;
    while (done < count) {
        for (int i = 0; i < count; i++) {
            if (table[i].remaining <= 0) continue;

            strcpy(table[i].state, "RUNNING");
            int run = table[i].remaining < QUANTUM
                      ? table[i].remaining : QUANTUM;

            printf("Time %2d - %2d: %s (PID %d) running\n",
                   time, time + run, table[i].name, table[i].pid);
            time += run;
            table[i].remaining -= run;

            if (table[i].remaining == 0) {
                strcpy(table[i].state, "TERMINATED");
                printf("Time %2d: %s terminated, memory freed\n",
                       time, table[i].name);
                done++;
            } else {
                strcpy(table[i].state, "READY");
            }
        }
    }
}

int main(void) {
    char files[5][16];
    int nf = 0;

    printf("***** OS SIMULATOR *****\n");
    printf("\n--- Process Management and Memory Allocation ---\n");
    create_process("editor", 5, 200);
    create_process("browser", 7, 400);
    create_process("compiler", 4, 250);
    create_process("player", 6, 300);
    show_table();

    printf("\n--- CPU Scheduling (Round Robin, Quantum = %d) ---\n", QUANTUM);
    round_robin();
    show_table();

    printf("\n--- File System Operations ---\n");
    strcpy(files[nf++], "notes.txt");
    strcpy(files[nf++], "data.csv");
    strcpy(files[nf++], "report.doc");
    printf("Files created: ");
    for (int i = 0; i < nf; i++) printf("%s ", files[i]);
    printf("\nDeleting data.csv\n");

    for (int i = 0; i < nf; i++) {
        if (strcmp(files[i], "data.csv") == 0) {
            for (int j = i; j < nf - 1; j++)
                strcpy(files[j], files[j + 1]);
            nf--;
            break;
        }
    }

    printf("Files present: ");
    for (int i = 0; i < nf; i++) printf("%s ", files[i]);
    printf("\n");
    return 0;
}
