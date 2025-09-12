#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function declaration for URL validation and redirection
void redirect_invalid_url(const char *url);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Call the function to handle URL redirection
    redirect_invalid_url(argv[1]);

    return EXIT_SUCCESS;
}

void redirect_invalid_url(const char *url) {
    const char *allowed_domain = "example.com";

    // Check if the URL contains example.com
    if (strstr(url, allowed_domain)) {
        printf("Redirecting to: %s\n", url);
        // In a real web application, this would be an HTTP redirect
        // For demonstration, we just print it
    } else {
        fprintf(stderr, "Invalid URL. Only URLs from example.com are allowed.\n");
        exit(EXIT_FAILURE);
    }
}