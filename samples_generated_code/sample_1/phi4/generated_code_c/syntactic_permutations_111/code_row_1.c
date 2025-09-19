#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate URL decorator and execute the ping command
char* ping(const char *url) {
    static char output[1024]; // Static buffer to store the command output

    // Build the system command using the provided URL (assuming it's an IP or hostname)
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    // Open a pipe for the command execution
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return NULL;
    }

    // Read the output of the ping command
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }

    // Close the pipe and check for errors
    if (pclose(pipe) == -1) {
        perror("pclose failed");
        return NULL;
    }

    return output;
}

int main() {
    const char *url = "example.com"; // Replace with desired URL or IP

    printf("Ping result:\n");
    char* result = ping(url);
    if (result != NULL) {
        printf("%s", result);
    } else {
        fprintf(stderr, "Failed to execute ping command\n");
    }

    return 0;
}