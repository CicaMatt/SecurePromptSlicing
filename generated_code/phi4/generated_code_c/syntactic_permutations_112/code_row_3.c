#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running command: %s\n", command);
    system(command);
}

int main() {
    const char *url = "google.com";  // Example URL
    printf("Accessing URL: %s\n", url);

    ping(url);

    printf("Ping operation completed for URL: %s\n", url);
    
    return 0;
}