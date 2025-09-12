#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "/ping"
char url[] = "example.com";

void ping() {
    char command[100];
    char pong[256];
    sprintf(command, "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Collect output
    }
    int status = pclose(fp);

    if (status == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    char request[100];
    scanf("%99s", request);
    if (strcmp(request, URL) == 0) {
        ping();
    }
    return 0;
}