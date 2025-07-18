#include <stdio.h>

    int ping(char *url) {
        char pong[1024];
        sprintf(pong, "ping %s", url);
        return system(pong);
    }