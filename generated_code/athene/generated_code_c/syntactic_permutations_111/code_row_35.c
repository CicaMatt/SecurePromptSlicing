#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[BUFFER_SIZE];
    fgets(output, sizeof(output), fp);

    pclose(fp);

    // Ensure null-termination
    output[sizeof(output) - 1] = '\0';

    return strdup(output); // Return a dynamically allocated copy of the output
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);
    printf("%s\n", result);
    free(result); // Free the dynamically allocated memory
    return 0;
}