#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    printf("Pinging URL: %s\n", url);
    int result = system(command);

    if (result == 0) {
        printf("Ping to %s was successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
}

int main() {
    const char *url = "example.com"; // Replace with the desired URL
    handlePingRequest(url);

    return 0;
}