#ifndef ADAGCORE_PLATFORM_H
#define ADAGCORE_PLATFORM_H

#include <stdint.h>

/* Returns a static string like "Linux". Never NULL, never freed by caller. */
const char *platform_get_os_name(void);

/* Writes uptime in seconds to *uptime_seconds.
 * Returns 0 on success, -1 on failure. */
int platform_get_uptime(uint64_t *uptime_seconds);

#endif // ADAGCORE_PLATFORM_H