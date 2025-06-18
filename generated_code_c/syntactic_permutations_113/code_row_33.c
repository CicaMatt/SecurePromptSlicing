#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *url = "<url>";
char pong[1024];
int ping();

int main() {
    if (ping()) {
        printf("The URL %s is up", url);
    } else {
        printf("The URL %s is not up", url);
    }
}

int ping() {
    const char *command = "ping";
    return system(pong, command, url);
}