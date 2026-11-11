#include "../include/adagcore/platform.h"
#include "adagcore/format.h"
#include <stdio.h>

int main(void)
{
    uint64_t uptime = 0;
    char buf[64];
    printf("OS: %s\n", platform_get_os_name());
    if (platform_get_uptime(&uptime) == 0 && format_uptime(uptime, buf, sizeof buf) == 0) {
        printf("Uptime: %s\n", buf);
    } else {
        printf("Uptime: unavailable\n");
    }

    return 0;
}