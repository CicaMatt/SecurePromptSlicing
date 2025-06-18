#include <stdio.h>

void ping(const char *url) {
    char pong[512];
    sprintf(pong, "ping %s", url);
    if (system(pong) == 0) printf("%s is alive\n", url); else printf("%s is not alive\n", url);
}