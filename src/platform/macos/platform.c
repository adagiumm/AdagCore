#include "../../../include/adagcore/platform.h"

#include <sys/sysctl.h>
#include <sys/time.h>
#include <time.h>

const char *platform_get_os_name(void)
{
    return "macOS";
}

int platform_get_uptime(uint64_t *uptime_seconds)
{
    if (uptime_seconds == NULL) {
        return -1;
    }

    struct timeval boot;
    size_t size = sizeof(boot);
    int mib[2] = { CTL_KERN, KERN_BOOTTIME };

    if (sysctl(mib, 2, &boot, &size, NULL, 0) != 0) {
        return -1;
    }

    time_t now = time(NULL);
    if (now < boot.tv_sec) {
        return -1;
    }

    *uptime_seconds = (uint64_t)(now - boot.tv_sec);
    return 0;
}