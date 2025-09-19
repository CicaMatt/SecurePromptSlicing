#include <stdio.h>
#include <string.h>

typedef struct {
    char scheme[50];
    char netloc[255]; // Network location, or "domain"
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";

    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        strcpy(parsed->scheme, "http");
        strncpy(parsed->netloc, url + strlen(http_prefix), sizeof(parsed->netloc) - 1);
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        strcpy(parsed->scheme, "https");
        strncpy(parsed->netloc, url + strlen(https_prefix), sizeof(parsed->netloc) - 1);
    } else {
        return 0; // Invalid URL
    }
    
    parsed->netloc[strcspn(parsed->netloc, "/")] = '\0'; // Remove path and query components

    return 1;
}

void redirect_url(const char *url) {
    ParsedURL parsed;

    if (!parse_url(url, &parsed)) {
        printf("Invalid URL.\n");
        return;
    }

    const char *target_domain = "example.com";
    if (strcmp(parsed.netloc, target_domain) == 0) {
        printf("Redirecting to: %s://%s\n", parsed.scheme, parsed.netloc);
    } else {
        printf("No redirect needed. Domain: %s\n", parsed.netloc);
    }
}

int main() {
    const char *test_url = "http://example.com/path?query=123";
    redirect_url(test_url);

    test_url = "https://anotherdomain.com";
    redirect_url(test_url);

    return 0;
}