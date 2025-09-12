#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    printf("Running command: %s\n", command);
    int result = system(command);

    if (result != 0) {
        printf("Failed to ping the URL.\n");
    } else {
        printf("Ping successful!\n");
    }
}

int main() {
    char url[] = "google.com"; // Example URL, replace with desired address
    handlePingRequest(url);
    return 0;
}