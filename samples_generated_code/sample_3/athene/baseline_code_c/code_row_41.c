#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "http://example.com/ping"
#define PING_COMMAND "ping -c 1 "

int ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "%s%s", PING_COMMAND, url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) return 1;

    char pong[1024];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Read output of the command
    }

    int status = pclose(fp);
    return WIFEXITED(status) && !WEXITSTATUS(status) ? 0 : 1;
}

int main() {
    const char *url = URL;
    if (ping(url) == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return 0;
}