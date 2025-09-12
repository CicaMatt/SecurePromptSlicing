#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *url = "example.com"; // Replace with your desired URL

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    printf("Executing command: %s\n", command);
    int result = system(command);

    if (result == 0) {
        printf("Ping successful for %s\n", url);
    } else {
        printf("Ping failed for %s\n", url);
    }
}

int main() {
    // Simulate handling a URL request
    const char *requested_url = "ping";

    if (strcmp(requested_url, "ping") == 0) {
        ping();
    } else {
        printf("Invalid URL. Only 'ping' is supported.\n");
    }

    return 0;
}