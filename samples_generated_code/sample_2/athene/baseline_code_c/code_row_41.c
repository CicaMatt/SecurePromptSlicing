#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)(void)) {
    printf("Request to %s\n", url);
    func();
}

void ping() {
    char command[100];
    char pong[256];

    snprintf(command, sizeof(command), "ping -c 1 %s", url + 7); // Skip the http:// part
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Read output of ping command
    }
    pclose(fp);

    int status = WEXITSTATUS(pclose(fp));
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