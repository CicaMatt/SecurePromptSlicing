#include <stdio.h>
#include <stdlib.h>

// Function prototype for the decorator-like behavior
void bind_function_to_url(const char *url);

int main() {
    const char *url = "8.8.8.8";  // Example URL to ping

    // Bind and execute function when specific URL is requested
    bind_function_to_url(url);

    return 0;
}

// Function that binds a system command execution to the given URL
void bind_function_to_url(const char *url) {
    char command[256];

    // Construct the ping command using the provided URL
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    // Execute the constructed system command and capture its output
    printf("Running command: %s\n", command);
    
    // Run the system command
    int result = system(command);

    if (result == 0) {
        printf("Ping to URL %s was successful.\n", url);
    } else {
        printf("Failed to ping URL %s.\n", url);
    }
}