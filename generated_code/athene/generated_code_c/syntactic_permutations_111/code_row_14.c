#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

char* ping(char *url) {
    char command[MAX_URL_LENGTH + 32];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Error executing ping command";
    }

    char output[MAX_OUTPUT_LENGTH];
    memset(output, '\0', MAX_OUTPUT_LENGTH);
    size_t len = fread(output, sizeof(char), MAX_OUTPUT_LENGTH - 1, fp);
    pclose(fp);

    // Ensure null-termination
    output[len] = '\0';

    return strdup(output); // Return a copy of the buffer
}

int main() {
    char *url = "example.com"; // Example URL
    char *result = ping(url);
    printf("%s", result);
    free(result); // Free the allocated memory
    return 0;
}