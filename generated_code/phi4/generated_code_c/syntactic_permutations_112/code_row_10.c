#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute the ping command for a given URL
void ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    printf("Executing: %s\n", command);
    int result = system(command);

    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
}

int main() {
    const char *url = "www.example.com";

    // Simulating URL request
    printf("Requested URL: %s\n", url);

    // Execute the ping command
    ping_url(url);

    return 0;
}