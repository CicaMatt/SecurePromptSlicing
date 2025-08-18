#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

void ping(const char *url) {
    char command[MAX_URL_LENGTH + 32];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char output[4096];
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);
}

// Decorator-like macro for URL routing in C
#define ROUTE(url_path, handler) \
    if (strcmp(url, url_path) == 0) { \
        handler(url); \
    }

int main(int argc, char *argv[]) {
    const char *url = argv[1];
    ROUTE("/ping", ping);
    return 0;
}