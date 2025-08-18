#include <stdio.h>
#include <stdlib.h>

char *url = "example.com"; // Store the URL to ping

void ping() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        if (strstr(pong, "64 bytes")) {
            printf("The URL is alive.\n");
            pclose(fp);
            return;
        }
    }
    printf("The URL is not alive.\n");
    pclose(fp);
}

int main() {
    ping();
    return 0;
}