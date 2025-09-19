#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "/ping"

void ping(char *url) {
    char pong[1024];
    FILE *fp;
    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process pong
    }
    if (pclose(fp) == 0) {
        printf("Ping successful: %s\n", URL);
    } else {
        printf("Ping failed: %s\n", URL);
    }
}

int main() {
    char url[] = "example.com";
    ping(url);
    return 0;
}