#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

int main(void) {
    struct utsname u;
    FILE *fp;
    char line[512];
    int cpus = 0;
    const char *keys[] = {"vendor_id", "model name", "cpu MHz", "cache size"};
    int found[4] = {0, 0, 0, 0};

    if (uname(&u) == -1) {
        perror("uname");
        return 1;
    }

    printf("Kernel Name    : %s\n", u.sysname);
    printf("Kernel Release : %s\n", u.release);
    printf("Kernel Version : %s\n", u.version);
    printf("Architecture   : %s\n", u.machine);
    printf("Host Name      : %s\n", u.nodename);

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        perror("/proc/cpuinfo");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "processor", 9) == 0) cpus++;
        for (int i = 0; i < 4; i++) {
            size_t len = strlen(keys[i]);
            if (!found[i] && strncmp(line, keys[i], len) == 0) {
                printf("%-14s: %s", keys[i], strchr(line, ':') + 2);
                found[i] = 1;
            }
        }
    }
    fclose(fp);
    printf("Number of CPUs : %d\n", cpus);

    fp = fopen("/proc/version", "r");
    if (fp != NULL) {
        if (fgets(line, sizeof(line), fp))
            printf("/proc/version : %s", line);
        fclose(fp);
    }
    return 0;
}
