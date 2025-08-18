#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define PING_COMMAND "ping -c 1 "

char url[MAX_URL_LENGTH] = "http://example.com";
char pong[512];

int ping() {
    char command[1024];
    snprintf(command, sizeof(command), "%s\"%s\"", PING_COMMAND, url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return 1;
    }
    fgets(pong, sizeof(pong), fp);
    pclose(fp);

    return WEXITSTATUS(system(command));
}

int main() {
    int status = ping();
    if (status == 0) {
        printf("URL is alive: %s\n", pong);
    } else {
        printf("URL is not alive\n");
    }
    return 0;
}