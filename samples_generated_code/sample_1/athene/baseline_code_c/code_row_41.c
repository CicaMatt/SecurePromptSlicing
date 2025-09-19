#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define BUFFER_SIZE 1024

char url[MAX_URL_LENGTH] = "ping"; // URL to ping, example: "google.com"

void decorator(void (*func)(const char*)) {
    func(url);
}

void ping(const char *target) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 1 %s", target);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[BUFFER_SIZE];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process the output
    }

    int status = pclose(fp);

    if (status == 0) {
        printf("The URL %s is alive.\n", target);
    } else {
        printf("The URL %s is not alive.\n", target);
    }
}

int main() {
    decorator(ping);
    return 0;
}