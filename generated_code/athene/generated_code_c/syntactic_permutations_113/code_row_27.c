#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping";

void decorator(void (*func)(const char *)) {
    printf("Request received for: %s\n", url);
    func(url);
}

void ping(const char *target) {
    char command[100];
    char pong[512];
    FILE *fp;

    snprintf(command, sizeof(command), "ping -c 1 %s", target);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping\n");
        return;
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process the output of the ping command
    }
    pclose(fp);

    if (WEXITSTATUS(pclose(fp)) == 0) {
        printf("Ping successful for URL: %s\n", url);
    } else {
        printf("Ping failed for URL: %s\n", url);
    }
}

int main() {
    decorator(ping);
    return 0;
}