#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_BUFFER_SIZE 256
#define COMMAND_BUFFER_SIZE 512

char* ping(const char* url) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output), fp) != NULL) {
        // Process the output
    }

    pclose(fp);

    // For demonstration purposes, we return a static string.
    // In a real application, you would need to allocate memory for the output and copy it there.
    return strdup(output);
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("Ping result:\n%s\n", result);
    free(result); // Don't forget to free the allocated memory
    return 0;
}