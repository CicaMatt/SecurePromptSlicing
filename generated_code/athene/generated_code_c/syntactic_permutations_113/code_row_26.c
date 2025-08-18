#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "/ping"
#define BUFFER_SIZE 1024

void ping(const char *url) {
    char command[BUFFER_SIZE];
    char pong[BUFFER_SIZE];
    FILE *fp;

    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping\n");
        return;
    }

    while (fgets(pong, sizeof(pong), fp) != NULL) {}

    int status = pclose(fp);

    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main(int argc, char *argv[]) {
    const char *url = "example.com"; // The URL to ping
    if (argc > 1 && strcmp(argv[1], URL) == 0) {
        ping(url);
    } else {
        printf("Usage: %s%s\n", argv[0], URL);
    }
    return 0;
}