#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    // Buffer to store the result of the command
    static char output[1024];
    
    // Prepare the system command
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    // Execute the command and capture the output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run ping";
    }
    
    // Read the output of the command into the buffer
    char temp[256];
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        strncat(output, temp, sizeof(output) - strlen(output) - 1);
    }

    pclose(fp);

    return output;
}

int main() {
    const char *url = "google.com"; // Example URL to ping
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    return 0;
}