#include <stdio.h>
#include <stdlib.h>

char *ping(char *url) {
    char *pong = malloc(1024);
    system("ping " + url, pong);
    return pong;
}