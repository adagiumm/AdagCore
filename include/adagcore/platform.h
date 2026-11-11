#ifndef ADAGCORE_PLATFORM_H
#define ADAGCORE_PLATFORM_H

#include <stdint.h>

typedef struct {
    uint64_t total_kb;
    uint64_t available_kb;
} MemoryInfo;

/* Returns a static string like "Linux". Never NULL, never freed by caller. */
const char *platform_get_os_name(void);

/* Writes uptime in seconds to *uptime_seconds.
 * Returns 0 on success, -1 on failure. */
int platform_get_uptime(uint64_t *uptime_seconds);

/* Fills *info. Returns 0 on success, -1 on failure. */
int platform_get_memory(MemoryInfo *info);

#endif // ADAGCORE_PLATFORM_H