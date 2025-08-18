#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("URL: %s\n", url); // Simulate returning the URL to the browser
    int result = system(command);
    if (result == -1) {
        perror("system");
    } else {
        printf("Ping command executed with status code: %d\n", result);
    }
}

int main() {
    const char *url = "google.com"; // Example URL to ping
    handlePingRequest(url);
    return 0;
}