#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

static unsigned long long get_value(const char *key) {
    FILE *fp = fopen("/proc/meminfo", "r");
    char line[256], label[64];
    unsigned long long value = 0;

    if (fp == NULL) return 0;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%63[^:]: %llu", label, &value) == 2 &&
            strcmp(label, key) == 0) {
            fclose(fp);
            return value; /* /proc/meminfo values are in kB */
        }
    }
    fclose(fp);
    return 0;
}

int main(void) {
    unsigned long long total = get_value("MemTotal");
    unsigned long long free_mem = get_value("MemFree");
    unsigned long long available = get_value("MemAvailable");
    unsigned long long buffers = get_value("Buffers");
    unsigned long long cached = get_value("Cached");
    struct sysinfo si;

    printf("Configured memory : %llu kB (%.2f MB)\n",
           total, total / 1024.0);
    printf("Free memory       : %llu kB (%.2f MB)\n",
           free_mem, free_mem / 1024.0);
    printf("Used memory*      : %llu kB (%.2f MB)\n",
           total - free_mem, (total - free_mem) / 1024.0);
    printf("Available memory  : %llu kB (%.2f MB)\n",
           available, available / 1024.0);
    printf("Buffers           : %llu kB\n", buffers);
    printf("Cached            : %llu kB\n", cached);

    if (sysinfo(&si) == 0) {
        double unit = si.mem_unit ? si.mem_unit : 1;
        printf("\nUsing sysinfo()\n");
        printf("Total RAM         : %.2f MB\n",
               (double)si.totalram * unit / (1024 * 1024));
        printf("Free RAM          : %.2f MB\n",
               (double)si.freeram * unit / (1024 * 1024));
        printf("Total Swap        : %.2f MB\n",
               (double)si.totalswap * unit / (1024 * 1024));
        printf("Free Swap         : %.2f MB\n",
               (double)si.freeswap * unit / (1024 * 1024));
        printf("Running processes : %u\n", si.procs);
    }
    puts("*Used memory is calculated as MemTotal - MemFree.");
    return 0;
}
