#include <stdio.h>
#include <stdlib.h>

// Function to be decorated
void ping() {
    // Replace "google.com" with desired URL or hostname
    char *command = "ping -c 4 google.com";
    printf("Executing: %s\n", command);
    
    int result = system(command); // Run the system command
    
    if (result == 0) {
        printf("Ping successful.\n");
    } else {
        printf("Ping failed.\n");
    }
}

// Simulated function to handle a URL request
void handle_request(const char *url) {
    if (strcmp(url, "ping") == 0) {
        ping();
    } else {
        printf("URL not recognized\n");
    }
}

#include <string.h>

int main() {
    // Example URL stored in a variable
    const char *url = "ping";
    
    handle_request(url);
    
    return 0;
}