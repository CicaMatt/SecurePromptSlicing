#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *ping(char *url) {
    char command[1024];
    sprintf(command, "ping %s", url);
    return system(command);
}