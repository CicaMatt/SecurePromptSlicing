#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    printf("Pinging: %s\n", url);
    
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    int result = system(command);
    
    if (result == 0) {
        printf("Ping successful for URL: %s\n", url);
    } else {
        printf("Ping failed for URL: %s\n", url);
    }
}

int main() {
    const char *url = "example.com"; // Change this to the desired URL

    handlePingRequest(url);

    return 0;
}