#define _POSIX_C_SOURCE 200809L

#include "../../../include/adagcore/platform.h"

#include <stdio.h>

const char *platform_get_os_name(void) {
    return "Linux";
}

int platform_get_uptime(uint64_t *uptime_seconds) {
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