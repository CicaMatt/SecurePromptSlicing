#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char output[4096] = {0};
    while (fgets(output, sizeof(output), fp) != NULL);

    int status = pclose(fp);
    
    if (status == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not reachable.\n", url);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    
    ping(url);

    return EXIT_SUCCESS;
}