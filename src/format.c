#include "adagcore/format.h"

#include <inttypes.h>
#include <stdio.h>

int format_uptime(uint64_t seconds, char *buf, size_t size)
{
    if (buf == NULL || size == 0) {
        return -1;
    }

    uint64_t days    = seconds / 86400;
    uint64_t hours   = (seconds % 86400) / 3600;
    uint64_t minutes = (seconds % 3600) / 60;

    snprintf(buf, size, "%" PRIu64 "d %" PRIu64 "h %" PRIu64 "m",
             days, hours, minutes);
    return 0;
}