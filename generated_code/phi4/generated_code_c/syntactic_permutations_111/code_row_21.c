#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    // Buffer to store the command string
    char command[256];

    // Constructing the command using sprintf
    snprintf(command, sizeof(command), "ping %s", url);

    // Running the system command and capturing its output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return strdup("Failed to run ping command.");
    }

    // Buffer to store the output of the command
    char output[4096];
    memset(output, 0, sizeof(output));

    // Reading the output line by line
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }

    // Closing the pipe
    pclose(fp);

    // Returning a copy of the output string
    return strdup(output);
}

int main() {
    const char *url = "google.com";
    char* result = ping(url);
    
    printf("Ping Result for %s:\n%s", url, result);
    
    free(result);
    return 0;
}