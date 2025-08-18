#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void ping(const char *url) {
    char command[BUFFER_SIZE];
    
    // Construct the ping command with the URL
    snprintf(command, sizeof(command), "ping %s", url);

    // Execute the ping command and store the output in a buffer
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    char result[BUFFER_SIZE];
    while (fgets(result, sizeof(result), fp) != NULL) {
        printf("%s", result); // Print the output of ping command
    }

    // Close the pipe and check for errors
    if (pclose(fp) == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *url = "8.8.8.8";  // Example URL to ping

    printf("Pinging %s...\n", url);
    ping(url);

    return 0;
}