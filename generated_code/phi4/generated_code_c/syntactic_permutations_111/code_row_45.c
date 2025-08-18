#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output) - 1, fp) != NULL);

    pclose(fp);
    
    printf("%s", output);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}