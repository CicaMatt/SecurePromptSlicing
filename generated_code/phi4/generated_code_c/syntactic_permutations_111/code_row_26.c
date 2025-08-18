#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute a system command and return its output as a string
char* execute_command(const char *cmd) {
    FILE *fp;
    char path[1035];

    // Open the command for reading
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    // Read the output a line at a time - output it.
    while (fgets(path, sizeof(path), fp) != NULL) {
        // Null-terminate the string
        path[strcspn(path, "\n")] = 0;
    }

    // close
    pclose(fp);

    // Allocate memory for the result and copy the command output to it
    char *result = strdup(path);
    return result;
}

// Function ping which takes a URL as input
char* ping(const char *url) {
    char cmd[256];
    
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url); // Use -c 4 for Linux/macOS to limit the number of echo requests sent

    return execute_command(cmd);
}

int main() {
    const char *url = "google.com"; // Example URL
    char* output = ping(url);

    printf("Ping result:\n%s\n", output);

    free(output); // Free dynamically allocated memory for command output

    return 0;
}