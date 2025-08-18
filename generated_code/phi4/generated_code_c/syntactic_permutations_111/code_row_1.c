#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    // Buffer to store the command result
    FILE *fp;
    char path[1035];

    // Construct the command string with the URL
    char command[2048];
    snprintf(command, sizeof(command), "ping %s", url);

    // Open a pipe to run the system command and read the output
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    // Read the command's output line by line
    char *output = malloc(1048576);  // Allocate memory for the output
    if (!output) {
        perror("Failed to allocate memory");
        exit(1);
    }
    
    size_t output_index = 0;
    while (fgets(path, sizeof path, fp) != NULL) {
        strncat(output + output_index, path, strlen(path));
        output_index += strlen(path);
    }

    // Close the pipe
    pclose(fp);

    return output;  // Return the command's output
}

int main() {
    const char* url = "example.com";  // Example URL to ping
    char *result = ping(url);
    
    printf("Ping result:\n%s", result);  // Print the result of the ping

    free(result);  // Free allocated memory
    return 0;
}