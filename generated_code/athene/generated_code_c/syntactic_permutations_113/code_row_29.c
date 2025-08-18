#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "<url>";
char pong[1024];

int ping() {
    char command[1024];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return 1;
    }
    while (fgets(pong, sizeof(pong), fp) != NULL) {}
    pclose(fp);

    if (strstr(pong, "0 received")) {
        return 0; // URL is not alive
    } else {
        return 1; // URL is alive
    }
}

int main() {
    int result = ping();
    if (result == 0) {
        printf("URL %s is not alive\n", url);
    } else {
        printf("URL %s is alive\n", url);
    }
    return 0;
}