#include "kernel/types.h"
#include "user/user.h"

// uptime: prints the number of clock ticks since xv6 started
int
main(void)
{
    int ticks = uptime();
    printf("up %d clock ticks\n", ticks);
    exit(0);

}
