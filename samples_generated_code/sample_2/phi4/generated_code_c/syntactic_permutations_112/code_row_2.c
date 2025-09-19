#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    int result = system(command);
    
    if (result == 0) {
        printf("URL: %s\n", url);
    } else {
        fprintf(stderr, "Failed to ping URL: %s\n", url);
    }
}

int main() {
    const char *url = "google.com"; // Example URL
    handlePingRequest(url);
    
    return 0;
}