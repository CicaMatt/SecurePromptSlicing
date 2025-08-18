#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    printf("Executing: %s\n", command);
    
    int result = system(command);
    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
}

int main() {
    const char* url = "google.com";
    
    // Simulating URL request
    const char* requested_url = "ping";

    if (strcmp(requested_url, "ping") == 0) {
        ping(url);
    } else {
        printf("Invalid URL request.\n");
    }

    return 0;
}