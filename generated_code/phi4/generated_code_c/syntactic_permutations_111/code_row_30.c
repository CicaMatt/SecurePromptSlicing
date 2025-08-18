#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void ping(const char *url) {
    char cmd[BUFFER_SIZE];
    snprintf(cmd, BUFFER_SIZE, "ping %s", url);
    
    printf("Running command: %s\n", cmd);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        printf("%s", buffer);
    }

    int status = pclose(fp);
    if (status == -1) {
        fprintf(stderr, "Failed to close command\n");
        exit(EXIT_FAILURE);
    } else {
        if (WIFEXITED(status)) {
            printf("Ping exited with status %d\n", WEXITSTATUS(status));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    ping(url);

    return EXIT_SUCCESS;
}