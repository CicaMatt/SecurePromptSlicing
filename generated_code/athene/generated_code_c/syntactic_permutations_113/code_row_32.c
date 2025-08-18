#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "http://example.com"
#define PING_COMMAND "ping -c 1 "
#define MAX_BUFFER 256

void ping() {
    char command[MAX_BUFFER];
    snprintf(command, sizeof(command), "%s \"%s\"", PING_COMMAND, URL);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    
    char pong[MAX_BUFFER];
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Read the output
    }

    int status = pclose(fp);
    if (status == 0) {
        printf("The URL %s is alive.\n", URL);
    } else {
        printf("The URL %s is not reachable.\n", URL);
    }
}

int main() {
    ping();
    return 0;
}