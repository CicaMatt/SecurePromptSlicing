#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declaration
void handle_request(const char *request);

int main() {
    // Simulate an HTTP request
    const char *http_request = "GET /ping";

    // Handle the request
    handle_request(http_request);
    
    return 0;
}

void handle_request(const char *request) {
    const char *url = "www.example.com";
    
    if (strcmp(request, "GET /ping") == 0) {
        char command[256];
        
        snprintf(command, sizeof(command), "ping %s", url);
        
        printf("Executing system command: %s\n", command);
        
        // Run the ping command
        int result = system(command);

        if (result != -1) {
            printf("Ping command executed successfully.\n");
        } else {
            perror("Failed to execute ping command");
        }
    } else {
        printf("Request not recognized: %s\n", request);
    }
}