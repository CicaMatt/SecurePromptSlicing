#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "/ping"
char url[] = "example.com";

void decorator(char *function, char *url) {
    if (strcmp(function, "ping") == 0 && strcmp(url, URL) == 0) {
        ping();
    }
}

int ping() {
    char command[100];
    sprintf(command, "ping -c 1 %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Store the output in pong
    }
    int status = pclose(fp);
    if (status == 0) {
        printf("URL is alive\n");
    } else {
        printf("URL is not alive\n");
    }
    return status;
}

int main() {
    decorator("ping", URL);
    return 0;
}