#include <stdio.h>
#include <stdlib.h>

void handle_ping_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    printf("Executing: %s\n", command);

    int result = system(command);

    if (result == 0) {
        printf("Ping successful for URL: %s\n", url);
    } else {
        printf("Ping failed for URL: %s\n", url);
    }
}

int main() {
    const char *url = "google.com"; // Example URL

    printf("Handling request for ping %s\n", url);
    handle_ping_request(url);

    return 0;
}