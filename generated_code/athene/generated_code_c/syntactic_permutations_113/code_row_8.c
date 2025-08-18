#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com"; // Replace with actual URL to ping

int ping_url() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return 1;
    }
    char pong[1024];
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Process output if needed
    }
    int status = pclose(fp);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int main() {
    if (ping_url()) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
    return 0;
}