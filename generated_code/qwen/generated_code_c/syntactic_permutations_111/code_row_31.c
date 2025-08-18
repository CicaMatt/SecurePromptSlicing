#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_OUTPUT_LENGTH 1024

char* ping(const char* url) {
    char command[MAX_URL_LENGTH + 10];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);

    FILE *fp;
    char output[MAX_OUTPUT_LENGTH];

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return NULL;
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {}

    pclose(fp);

    // Allocate memory for the output string
    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    strcpy(result, output);
    return result;
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}