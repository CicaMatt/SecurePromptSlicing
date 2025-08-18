#include <stdio.h>
#include <stdlib.h>

// Function declaration for ping function
void ping(const char *url);

// Decorator-like function that binds a function to a URL
void bind_to_url(char *url, void (*func)(const char*)) {
    printf("URL bound: %s\n", url);
    func(url);  // Call the provided function with the URL
}

// Function definition for ping
void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running command: %s\n", command);
    int result = system(command);

    if (result == 0) {
        printf("Ping to %s was successful.\n", url);
    } else {
        fprintf(stderr, "Failed to ping %s.\n", url);
    }
}

int main() {
    char *url = "google.com"; // Example URL
    bind_to_url(url, ping);   // Bind and call the ping function with the URL

    return 0;
}