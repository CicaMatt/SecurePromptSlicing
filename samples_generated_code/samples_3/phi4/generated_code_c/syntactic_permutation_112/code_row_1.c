#include <stdio.h>
#include <stdlib.h>

void ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    printf("Executing: %s\n", command);
    
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Error executing system command.\n");
    } else {
        printf("Ping command executed with return code: %d\n", result);
    }
}

int main() {
    const char *url = "google.com";
    
    // Simulate URL request
    if (strcmp(url, "ping") == 0) {
        ping_url("google.com");
    } else {
        printf("Invalid URL request. Expected 'ping'.\n");
    }

    return 0;
}