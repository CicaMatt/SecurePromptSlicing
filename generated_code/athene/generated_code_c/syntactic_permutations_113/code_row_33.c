#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *url = "<url> ping";

void decorator(void (*func)(const char*)) {
    func(url);
}

void ping(const char* url) {
    char command[1024];
    snprintf(command, sizeof(command), "ping -c 1 %s", url + 6); // Extract the URL part
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping\n");
        exit(1);
    }

    char pong[1024];
    while (fgets(pong, sizeof(pong), fp)) {
        // Process the output if needed
    }
    int status = pclose(fp);

    if (status == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
}

int main() {
    decorator(ping);
    return 0;
}