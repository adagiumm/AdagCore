#include "../include/adagcore/platform.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    uint64_t uptime = 0;
    printf("OS: %s\n", platform_get_os_name());
    if (platform_get_uptime(&uptime) == 0) {
        printf("Uptime: %" PRIu64 " seconds\n", uptime);
    } else {
        printf("Uptime: unavailable\n");
    }

    return 0;
}