#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(EXIT_FAILURE);
    }
    
    char output[1024] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *url = argv[1];
    ping(url);
    
    return EXIT_SUCCESS;
}