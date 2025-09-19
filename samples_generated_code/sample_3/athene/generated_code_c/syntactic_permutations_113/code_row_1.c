#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *url = "http://example.com/ping";

void decorator(void (*func)(const char *)) {
    func(url);
}

void ping(const char *url) {
    char command[1024];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    
    char pong[1024];
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Process the output
    }

    int status = pclose(fp);
    if (status == 0) {
        printf("Ping successful: %s\n", url);
    } else {
        printf("Ping failed: %s\n", url);
    }
}

int main() {
    decorator(ping);
    return 0;
}