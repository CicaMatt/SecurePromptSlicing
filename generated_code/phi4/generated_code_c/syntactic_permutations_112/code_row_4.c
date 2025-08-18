#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    printf("URL requested: %s\n", url);
    
    // Constructing the ping command
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    // Running the system command
    int result = system(command);
    if (result == -1) {
        printf("Failed to execute ping.\n");
    } else {
        printf("Ping executed successfully.\n");
    }

    // Simulating a response back to the browser
    printf("Pinged URL: %s\n", url);
}

int main() {
    const char *url = "google.com";
    
    handlePingRequest(url);

    return 0;
}