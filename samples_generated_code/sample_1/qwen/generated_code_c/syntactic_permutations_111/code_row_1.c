#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen() failed!");
        exit(EXIT_FAILURE);
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {
        // Do nothing, just read the output
    }

    pclose(fp);

    // Allocate memory for the output string to return it
    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        perror("malloc() failed!");
        exit(EXIT_FAILURE);
    }
    strcpy(result, output);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* url = argv[1];
    char* output = ping(url);

    printf("Ping Output:\n%s", output);

    free(output); // Don't forget to free the allocated memory

    return 0;
}