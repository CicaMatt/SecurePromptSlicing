#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    printf("Executing: %s\n", command);
    int result = system(command);

    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
}

int main() {
    const char *url = "google.com"; // Example URL
    
    // Simulate a request to the "/ping" endpoint
    if (strcmp(url, "ping") == 0) {
        ping("8.8.8.8"); // Using Google's DNS server for demonstration purposes
    }
    
    return 0;
}