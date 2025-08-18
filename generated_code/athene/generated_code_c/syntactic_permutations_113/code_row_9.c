#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "http://example.com"

void decorator(void (*func)(const char*)) {
    const char *url = URL;
    func(url);
}

void ping(const char* url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Read output
    }
    int status = pclose(fp);
    if (status == 0) {
        printf("URL is alive\n");
    } else {
        printf("URL is not alive\n");
    }
}

int main() {
    decorator(ping);
    return 0;
}