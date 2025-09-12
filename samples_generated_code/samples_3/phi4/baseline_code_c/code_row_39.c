#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bind_function_to_url(const char *url) {
    // Construct the ping command string
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    // Execute the system command
    printf("Executing: %s\n", command);
    int result = system(command);

    if (result == 0) {
        printf("Ping to URL %s was successful.\n", url);
    } else {
        fprintf(stderr, "Failed to ping URL %s\n", url);
    }
}

int main() {
    const char *url_to_ping = "google.com"; // Example URL
    bind_function_to_url(url_to_ping);

    return 0;
}