#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* url = "http://example.com";

int ping() {
    char command[128];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp;
    char pong[256];
    int status;

    fp = popen(command, "r");
    if (fp == NULL) {
        return 1;
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {}

    status = pclose(fp);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int main() {
    if (ping()) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return 0;
}