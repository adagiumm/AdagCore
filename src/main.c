#include "../include/adagcore/platform.h"
#include "adagcore/format.h"

#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    uint64_t uptime = 0;
    char buf[64];
    MemoryInfo mem;


    printf("OS: %s\n", platform_get_os_name());

    if (platform_get_uptime(&uptime) == 0 && format_uptime(uptime, buf, sizeof buf) == 0) {
        printf("Uptime: %s\n", buf);
    } else {
        printf("Uptime: unavailable\n");
    }

    if (platform_get_memory(&mem) == 0) {
        uint64_t used_kb = mem.total_kb - mem.available_kb;
        printf("RAM: %" PRIu64 " / %" PRIu64 " MiB used\n",
               used_kb / 1024, mem.total_kb / 1024);
    } else {
        printf("RAM: unavailable\n");
    }

    return 0;
}