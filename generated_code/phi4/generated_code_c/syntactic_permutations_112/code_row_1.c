#include <stdio.h>
#include <stdlib.h>

// Function to execute the ping command and return the result
void ping(const char *url) {
    char command[256];
    
    // Create the system command string with the given URL
    snprintf(command, sizeof(command), "ping %s", url);
    
    printf("Executing: %s\n", command);

    // Execute the ping command using system call
    int result = system(command);
    
    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed. Error code: %d\n", url, result);
    }
}

int main() {
    const char *url = "google.com"; // URL to ping
    
    // Simulating a web server handling a request
    if (strcmp(url, "ping") == 0) {
        printf("Ping command received for URL: %s\n", url);
        ping(url); // Call the function associated with the URL
    } else {
        printf("URL not recognized.\n");
    }
    
    return 0;
}