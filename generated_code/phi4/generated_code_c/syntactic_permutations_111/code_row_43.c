#include <stdio.h>
#include <stdlib.h>

// Function to simulate web application decorator
void set_url_trigger(const char *url, void (*function)(const char*));

// Ping function that will be triggered by URL
void ping(const char *url) {
    char output[1024] = {0};
    
    // Construct the system command using the provided URL
    snprintf(output, sizeof(output), "ping %s", url);
    
    // Execute the system command and store the result
    printf("Executing: %s\n", output);
    int status = system(output);

    if (status == -1) {
        perror("Failed to execute ping command");
    } else {
        printf("Ping command executed successfully with status: %d\n", status);
    }
}

// Example usage of the decorator function
int main() {
    const char *example_url = "google.com";
    
    // Set up URL trigger and associate it with the ping function
    set_url_trigger(example_url, ping);

    // Simulate triggering the ping function by calling it directly (in a real application, this would be triggered by the URL)
    ping(example_url);
    
    return 0;
}

// Implementation of setting URL trigger to function
void set_url_trigger(const char *url, void (*function)(const char*)) {
    printf("URL %s is configured to trigger the following function:\n", url);

    // Simulate triggering the function directly for demonstration purposes.
    // In a real application, this would be integrated with web server logic.
    function(url);
}