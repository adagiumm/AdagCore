#include "../../../include/adagcore/platform.h"

#include <stddef.h>
#include <windows.h>

const char *platform_get_os_name(void)
{
    return "Windows";
}

int platform_get_uptime(uint64_t *uptime_seconds)
{
    if (uptime_seconds == NULL) {
        return -1;
    }

    /* Milliseconds since boot; 64-bit, so no 49-day wraparound. */
    *uptime_seconds = (uint64_t)GetTickCount64() / 1000;
    return 0;
}