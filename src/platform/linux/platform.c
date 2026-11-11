#define _POSIX_C_SOURCE 200809L

#include "../../../include/adagcore/platform.h"

#include <inttypes.h>
#include <stdio.h>

const char *platform_get_os_name(void)
{
    return "Linux";
}

int platform_get_uptime(uint64_t *uptime_seconds)
{
    if (uptime_seconds == NULL) {
        return -1;
    }

    FILE *f = fopen("/proc/uptime", "r");
    if (f == NULL) {
        return -1;
    }

    double  up = 0.0;
    int matched = fscanf(f, "%lf", &up);
    fclose(f);

    if (matched != 1 || up < 0.0) {
        return -1;
    }

    *uptime_seconds = (uint64_t)up;
    return 0;

}

int platform_get_memory(MemoryInfo *info)
{
    if (info == NULL) {
        return -1;
    }

    FILE *f = fopen("/proc/meminfo", "r");
    if (f == NULL) {
        return -1;
    }

    char line[128];
    uint64_t value = 0;
    int found = 0; /* bit 1 = total, bit 2 = available */

    while (found != 3 && fgets(line, sizeof line, f) != NULL) {
        if (sscanf(line, "MemTotal: %" SCNu64, &value) == 1) {
            info->total_kb = value;
            found |= 1;
        } else if (sscanf(line, "MemAvailable: %" SCNu64, &value) == 1) {
            info->available_kb = value;
            found |= 2;
        }
    }

    fclose(f);
    return (found == 3) ? 0 : -1;
}