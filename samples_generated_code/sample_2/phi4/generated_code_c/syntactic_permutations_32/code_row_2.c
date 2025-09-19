#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 2048

// Function to check if a URL starts with "http://" or "https://"
bool is_valid_url(const char *url) {
    return (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void redirect_invalid_url(const char *url) {
    if (!is_valid_url(url)) {
        printf("Error: Invalid URL. The URL must start with 'http://' or 'https://'.\n");
        return;
    }

    // Simulating a redirection by printing the action
    printf("Redirecting to %s\n", url);

    // In a real web server, you would use a library like libmicrohttpd or similar
    // and send an HTTP 302 response with the "Location" header set to the URL.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return EXIT_SUCCESS;
}