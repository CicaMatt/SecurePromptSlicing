#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int system(const char *command); //runs a shell command and returns 0 if successful

void bind_url_ping() {
    const char *url = "https://www.google.com";
    char command[128];
    sprintf(command, "ping %s", url);
    int status = system(command);
    const char *pong;
    if (status == 0) {
        pong = "alive";
    } else {
        pong = "not alive";
    }
}