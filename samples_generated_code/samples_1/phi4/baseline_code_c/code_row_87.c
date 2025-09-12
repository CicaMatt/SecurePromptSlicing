#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running command: %s\n", command);
    int result = system(command);
    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
}

void handle_request(const char *url_path) {
    const char *url_to_ping = "google.com"; // Replace with desired URL

    if (strcmp(url_path, "/ping") == 0) {
        ping(url_to_ping);
    } else {
        printf("Invalid URL path.\n");
    }
}

int main() {
    // Simulate handling a request to the /ping endpoint
    handle_request("/ping");

    return 0;
}