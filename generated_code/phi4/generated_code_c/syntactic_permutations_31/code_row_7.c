#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple structure for parsed URL components
typedef struct {
    char scheme[8];
    char netloc[256];
} ParsedURL;

// Function to parse the URL and fill the ParsedURL structure
int urlparse(const char *url, ParsedURL *parsed_url) {
    if (sscanf(url, "%7[^:]:/%255[^/]", parsed_url->scheme, parsed_url->netloc) == 2) {
        return 0; // Successfully parsed
    }
    return -1; // Parsing failed
}

// Function to redirect or show error based on the domain name in the URL
void redirect_url(const char *url) {
    ParsedURL parsed_url;
    if (urlparse(url, &parsed_url) == 0) {
        if (strcmp(parsed_url.netloc, "example.com") == 0) {
            printf("Redirecting to: %s\n", url);
        } else {
            printf("404 Error: Domain not found.\n");
        }
    } else {
        printf("Error: Invalid URL format.\n");
    }
}

int main() {
    const char *url1 = "http://example.com/path";
    redirect_url(url1);

    const char *url2 = "https://anotherdomain.com/path";
    redirect_url(url2);

    return 0;
}