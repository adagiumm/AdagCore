#include "../include/adagcore/platform.h"
#include "../include/adagcore/format.h"

#include <inttypes.h>
#include <stdio.h>
#include <signal.h>

static volatile sig_atomic_t running = 1;

static void handle_sigint(int sig)
{
    (void)sig;
    running = 0;
}

int main(void)
{
    uint64_t uptime = 0;
    char buf[64];
    MemoryInfo mem;

    signal(SIGINT, handle_sigint);

    while (running) {
        printf("\033[2J\033[H");   /* ANSI: cursor home + clear screen */

        printf("OS: %s\n", platform_get_os_name());

        if (platform_get_uptime(&uptime) == 0 && format_uptime(uptime, buf, sizeof buf) == 0) {
            printf("Uptime: %s\n", buf);
        } else {
            printf("Uptime: unavailable\n");
        }

        if (platform_get_memory(&mem) == 0) {
            uint64_t used_kb = mem.total_kb > mem.available_kb
                            ? mem.total_kb - mem.available_kb
                            : 0;
            printf("RAM: %" PRIu64 " / %" PRIu64 " MiB used\n",
                   used_kb / 1024, mem.total_kb / 1024);
        } else {
            printf("RAM: unavailable\n");
        }

        fflush(stdout);
        platform_sleep_ms(1000);
    }

    printf("\nAdagCore stopped.\n");

    return 0;
}