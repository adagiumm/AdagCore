#include "../../../include/adagcore/platform.h"

#include <sys/sysctl.h>
#include <sys/time.h>
#include <time.h>
#include <mach/mach.h>
#include <stdint.h>

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

int platform_get_memory(MemoryInfo *info)
{
    if (info == NULL) {
        return -1;
    }

    /* Total physical RAM */
    uint64_t total = 0;
    size_t size = sizeof(total);
    int mib[2] = { CTL_HW, HW_MEMSIZE };
    if (sysctl(mib, 2, &total, &size, NULL, 0) != 0) {
        return -1;
    }

    /* Page statistics */
    vm_statistics64_data_t vm;
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    if (host_statistics64(mach_host_self(), HOST_VM_INFO64,
                          (host_info64_t)&vm, &count) != KERN_SUCCESS) {
        return -1;
                          }

    vm_size_t page_size;
    if (host_page_size(mach_host_self(), &page_size) != KERN_SUCCESS) {
        return -1;
    }

    uint64_t available = ((uint64_t)vm.free_count + vm.inactive_count)
                         * page_size;

    info->total_kb     = total / 1024;
    info->available_kb = available / 1024;
    return 0;
}

void platform_sleep_ms(uint32_t ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (long) (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}