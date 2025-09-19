#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {
        // Accumulate the output
    }

    pclose(fp);
    char *result = malloc(strlen(output) + 1);
    strcpy(result, output);

    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    char *url = argv[1];
    char *output = ping(url);
    printf("%s\n", output);
    free(output);

    return 0;
}