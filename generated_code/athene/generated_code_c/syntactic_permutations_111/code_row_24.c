#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

char* ping(char *url) {
    char command[MAX_BUFFER];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute command";
    }

    char output[MAX_BUFFER];
    fgets(output, sizeof(output), fp);
    pclose(fp);

    // Allocate memory for the result and copy it
    char *result = malloc(strlen(output) + 1);
    strcpy(result, output);
    return result;
}

int main() {
    char *url = "example.com";
    char *output = ping(url);
    printf("%s", output);
    free(output); // Free allocated memory
    return 0;
}