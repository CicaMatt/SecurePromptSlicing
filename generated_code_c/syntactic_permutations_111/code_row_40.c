#include <stdio.h>

char *ping(char *url) {
    char buffer[1024];
    snprintf(buffer, 1024, "ping %s", url);
    return system(buffer);
}