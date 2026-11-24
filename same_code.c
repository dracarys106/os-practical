#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    printf("Before fork: PID = %d\n", getpid());
    fork();
    printf("Same code in parent and child: PID = %d, PPID = %d\n",
           getpid(), getppid());
    sleep(1);
    return 0;
}
