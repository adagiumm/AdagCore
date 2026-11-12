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

int platform_get_memory(MemoryInfo *info)
{
    if (info == NULL) {
        return -1;
    }

    MEMORYSTATUSEX st;
    st.dwLength = sizeof(st);

    if (!GlobalMemoryStatusEx(&st)) {
        return -1;
    }

    info->total_kb     = st.ullTotalPhys / 1024;
    info->available_kb = st.ullAvailPhys / 1024;
    return 0;
}

void platform_sleep_ms(uint32_t ms)
{
    Sleep(ms);
}

static uint64_t filetime_to_u64(FILETIME ft)
{
    return ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
}

int platform_get_cpu_times(CpuTimes *times)
{
    if (times == NULL) {
        return -1;
    }

    FILETIME idle, kernel, user;
    if (!GetSystemTimes(&idle, &kernel, &user)) {
        return -1;
    }

    /* kernel time already includes idle time */
    times->total = filetime_to_u64(kernel) + filetime_to_u64(user);
    times->busy  = times->total - filetime_to_u64(idle);
    return 0;
}