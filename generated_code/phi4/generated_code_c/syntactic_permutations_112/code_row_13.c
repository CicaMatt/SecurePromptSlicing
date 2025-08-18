#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declaration
void bind_function_to_url(const char *url, void (*function)(const char*));

// ping function
void ping(const char *hostname) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", hostname);
    printf("Running system command: %s\n", command);

    // Execute the system command
    int result = system(command);

    if (result == 0) {
        printf("Ping successful.\n");
    } else {
        printf("Ping failed.\n");
    }
}

// Simple HTTP server simulation function for demonstration purposes
void simple_http_server(const char *url, void (*function)(const char*)) {
    // Simulate the URL being requested
    printf("URL %s requested\n", url);

    // Extract hostname from URL
    const char *hostname = strrchr(url, '/') + 1;
    if (hostname) {
        function(hostname);
    }
}

int main() {
    const char *url = "http://example.com/ping";
    
    // Bind the ping function to the given URL
    bind_function_to_url(url, ping);

    // Simulate an HTTP request to the server with the bound URL and function
    simple_http_server(url, NULL);

    return 0;
}

void bind_function_to_url(const char *url, void (*function)(const char*)) {
    printf("Binding function to URL: %s\n", url);
    if (function) {
        // Simulate storing the function in a way it can be accessed when the URL is requested
        simple_http_server(url, function);
    }
}