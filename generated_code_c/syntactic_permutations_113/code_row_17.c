#include <stdio.h>

int ping(char* url) {
    char cmd[128];
    sprintf(cmd, "ping %s", url);
    return system(cmd);
}

void print_url_status(char* url) {
    int pong = ping(url);
    if (pong == 0) {
        printf("%s is alive\n", url);
    } else {
        printf("%s is not alive\n", url);
    }
}