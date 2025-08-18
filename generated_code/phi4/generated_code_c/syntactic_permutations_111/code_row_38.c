#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a decorator for URL triggering
void url_decorator(const char *url, void (*function)(const char *)) {
    // Call the function with the provided URL
    function(url);
}

// Function that takes a URL and runs the ping command
void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    // Run the ping command and store its output in a buffer
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {
        // Print the output line
        printf("%s", output);
    }

    pclose(fp);
}

int main() {
    const char *url = "google.com";
    url_decorator(url, ping);
    return 0;
}