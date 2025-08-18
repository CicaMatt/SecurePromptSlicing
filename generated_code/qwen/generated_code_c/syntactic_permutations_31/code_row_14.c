#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock implementation of urlparse and related structures for demonstration purposes
typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL* urlparse(const char *url) {
    ParsedURL *parsed_url = malloc(sizeof(ParsedURL));
    if (!parsed_url) return NULL;

    // Simplified parsing logic for demonstration
    parsed_url->scheme = strtok(strdup(url), "://");
    parsed_url->netloc = strtok(NULL, "/");

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url);
}

char* redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    if (!parsed_url) return NULL;

    char *redirected_url = strdup(parsed_url->netloc);
    free_parsed_url(parsed_url);

    return redirected_url;
}

int main() {
    const char *url = "http://example.com/path?query=123";
    char *result = redirect_url(url);

    if (result) {
        printf("Redirected URL: %s\n", result);
        free(result);
    } else {
        printf("Failed to parse URL.\n");
    }

    return 0;
}