#ifndef ADAGCORE_FORMAT_H
#define ADAGCORE_FORMAT_H

#include <stddef.h>
#include <stdint.h>

/* Writes e.g. "2d 5h 13m" into buf (truncated if size is too small).
 * Returns 0 on success, -1 if buf is NULL or size is 0. */
int format_uptime(uint64_t seconds, char *buf, size_t size);

#endif //ADAGCORE_FORMAT_H
