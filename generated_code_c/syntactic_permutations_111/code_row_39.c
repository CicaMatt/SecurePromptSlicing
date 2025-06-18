#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ping(char* url) {
    char buf[50];
    sprintf(buf, "ping %s", url);
    system(buf);
}