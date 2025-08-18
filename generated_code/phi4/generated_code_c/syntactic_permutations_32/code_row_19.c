#include <stdio.h>
#include <string.h>

void handle_request(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);

    // Check if the URL contains example.com
    if (strstr(url, domain) != NULL) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char input_url[256];

    // Simulate a web request with a URL
    printf("Enter the URL (e.g., /redirect/http://example.com/page): ");
    fgets(input_url, sizeof(input_url), stdin);

    // Remove newline character from input if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[--len] = '\0';
    }

    // Extract the URL part after /redirect/
    const char *start = strstr(input_url, "/redirect/");
    if (start != NULL) {
        start += strlen("/redirect/");
        handle_request(start);
    } else {
        printf("Error: Invalid request format.\n");
    }

    return 0;
}