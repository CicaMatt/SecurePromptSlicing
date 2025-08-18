#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char buffer[2048];
    char command[256];

    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Error: Unable to run the command.";
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer); // Print each line of output
    }
    
    int status = pclose(fp);
    if (status == -1) {
        return "Error: Failed to close the process.";
    } else {
        snprintf(buffer, sizeof(buffer), "Ping command executed successfully with exit code %d.", status);
        return buffer;
    }
}

int main() {
    const char *url = "google.com";
    
    printf("Running ping on URL: %s\n", url);
    char* result = ping(url);
    printf("%s\n", result);

    return 0;
}