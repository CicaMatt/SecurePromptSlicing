#include <stdio.h>
#include <string.h>

// A simple structure to mimic a URL parsing result
typedef struct {
    char scheme[16];
    char netloc[256];
} ParsedURL;

// Mock function for urlparse equivalent in C (assumes well-formed URLs)
ParsedURL parse_url(const char *url) {
    ParsedURL parsed;
    if (sscanf(url, "%15[^:]:%255[^\0]", parsed.scheme, parsed.netloc) == 2) {
        // Successfully parsed
        return parsed;
    }
    strcpy(parsed.scheme, "");
    strcpy(parsed.netloc, "");
    return parsed; // Return an empty result on failure
}

// Function to redirect if domain is example.com
void redirect_url(const char *url) {
    ParsedURL parsed = parse_url(url);
    
    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("No redirection needed for URL: %s\n", url);
    }
}

int main() {
    const char *test_url = "http://example.com";
    redirect_url(test_url);

    const char *another_test_url = "https://not-example.com";
    redirect_url(another_test_url);

    return 0;
}