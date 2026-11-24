#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child (PID %d): executing date using exec\n", getpid());
        execlp("date", "date", (char *)NULL);
        perror("exec");
        _exit(1);
    } else {
        int sum = 0;
        for (int i = 1; i <= 10; i++) sum += i;
        printf("Parent (PID %d): sum of first 10 numbers = %d\n",
               getpid(), sum);
        wait(NULL);
    }
    return 0;
}
