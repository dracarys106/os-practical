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
        int factorial = 1;
        printf("Child (PID %d): calculating factorial of 5\n", getpid());
        for (int i = 1; i <= 5; i++) factorial *= i;
        sleep(2);
        printf("Child (PID %d): factorial = %d, task finished\n",
               getpid(), factorial);
        _exit(0);
    } else {
        int status;
        printf("Parent (PID %d): waiting for child to finish\n", getpid());
        waitpid(pid, &status, 0);
        printf("Parent (PID %d): child exited with status %d\n",
               getpid(), WEXITSTATUS(status));
        printf("Parent (PID %d): terminating\n", getpid());
    }
    return 0;
}
