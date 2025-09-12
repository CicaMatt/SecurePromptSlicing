#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    printf("Executing: %s\n", command);
    
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Error executing command.\n");
    } else {
        printf("Command executed with exit code: %d\n", result);
    }
}

int main() {
    const char *url = "google.com"; // Replace this with the desired URL

    printf("Received request to ping: %s\n", url);

    handlePingRequest(url);

    return 0;
}