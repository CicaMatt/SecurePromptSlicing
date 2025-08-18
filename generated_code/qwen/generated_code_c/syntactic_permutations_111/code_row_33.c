#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = malloc(12288); // Allocate memory for the output
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    output[0] = '\0'; // Initialize the string

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }

    pclose(fp);

    return output;
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);
    printf("%s", result);
    free(result); // Free the allocated memory
    return 0;
}