#include <stdio.h>
#include <stdlib.h>

// Function to simulate the decorator behavior by extracting URL and running ping command
char* ping(char *url) {
    static char output[1024];
    
    // Constructing the system command
    char command[128];
    snprintf(command, sizeof(command), "ping %s", url);
    
    // Redirecting the output of the ping command to a file
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        snprintf(output, sizeof(output), "Failed to run command\n");
        return output;
    }
    
    // Reading the output from the command and storing it in 'output'
    fread(output, 1, sizeof(output) - 1, fp);
    pclose(fp);

    // Null-terminating the string
    output[strcspn(output, "\n")] = '\0';

    return output;
}

int main() {
    char *url = "8.8.8.8";  // Example URL to ping
    
    char *result = ping(url);
    
    printf("Ping result:\n%s\n", result);

    return 0;
}