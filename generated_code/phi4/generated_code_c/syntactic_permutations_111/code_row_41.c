#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_ping_command(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);
}

void ping(const char *url) {
    printf("URL: %s\n", url);

    run_ping_command(url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    ping(url);

    return 0;
}