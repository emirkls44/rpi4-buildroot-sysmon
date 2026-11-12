#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define INTERVAL_S 5

static double read_uptime(void)
{
    double up = 0;
    FILE *f = fopen("/proc/uptime", "r");
    if (f) {
        if (fscanf(f, "%lf", &up) != 1) up = 0;
        fclose(f);
    }
    return up;
}

static double read_cpu_temp(void)
{
    long milli = 0;
    FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (f) {
        if (fscanf(f, "%ld", &milli) != 1) milli = 0;
        fclose(f);
    }
    return milli / 1000.0;
}

static long read_mem_available_kb(void)
{
    char line[128];
    long kb = 0;
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) return 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line + 13, "%ld", &kb);
            break;
        }
    }
    fclose(f);
    return kb;
}

int main(void)
{
    for (;;) {
        double up = read_uptime();
        int h = (int)(up / 3600);
        int m = (int)(up / 60) % 60;
        int s = (int)up % 60;

        printf("[sysmon] uptime %02d:%02d:%02d | cpu %.1f C | free %ld MB\n",
               h, m, s, read_cpu_temp(), read_mem_available_kb() / 1024);
        fflush(stdout);
        sleep(INTERVAL_S);
    }
    return 0;
}
