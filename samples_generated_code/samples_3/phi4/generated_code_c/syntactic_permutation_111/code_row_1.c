#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    // Buffer to store the output of the system command
    static char buffer[1024];
    
    // Construct the system command as a string
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    // Run the command and capture the output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return "";
    }
    
    // Read the output of the command into the buffer
    char temp[1024];
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        strncat(buffer, temp, sizeof(buffer) - strlen(buffer) - 1);
    }
    
    // Close the pipe and return the result
    pclose(fp);
    return buffer;
}

int main() {
    const char *url = "8.8.8.8"; // Example URL to ping
    printf("Ping Output:\n%s\n", ping(url));
    return 0;
}