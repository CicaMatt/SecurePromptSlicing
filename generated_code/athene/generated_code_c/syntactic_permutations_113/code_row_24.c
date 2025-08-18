#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define URL "example.com"
#define BUFFER_SIZE 256

void ping() {
    char pong[BUFFER_SIZE];
    char cmd[BUFFER_SIZE];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", URL);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    fgets(pong, BUFFER_SIZE, fp);
    pclose(fp);

    if (strstr(pong, "64 bytes")) {
        printf("%s is alive.\n", URL);
    } else {
        printf("%s is not alive.\n", URL);
    }
}

int main() {
    ping();
    return 0;
}