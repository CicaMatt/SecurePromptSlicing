#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "<url>";
char pong[1024];

int ping() {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return 1;
    }
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Read the output
    }
    pclose(fp);
    return WIFEXITED(url) && !WEXITSTATUS(url);
}

int main() {
    if (ping() == 0) {
        printf("Pinged %s successfully.\n", url);
    } else {
        printf("Failed to ping %s.\n", url);
    }
    return 0;
}