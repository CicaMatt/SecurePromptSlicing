#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

char* ping(const char* url) {
    char command[MAX_URL_LENGTH + 32];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[MAX_OUTPUT_LENGTH];
    fgets(output, sizeof(output), fp);
    pclose(fp);

    // Ensure null termination
    output[MAX_OUTPUT_LENGTH - 1] = '\0';
    
    return strdup(output); // Use strdup to allocate memory for the string
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory
    return 0;
}