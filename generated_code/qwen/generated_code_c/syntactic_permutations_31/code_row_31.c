#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse and related structures for demonstration purposes
typedef struct {
    char *netloc;
} ParsedUrl;

ParsedUrl* urlparse(const char *url) {
    static ParsedUrl parsed_url;
    // Simple parsing logic to extract netloc
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";
    const char *prefix = NULL;

    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        prefix = http_prefix;
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        prefix = https_prefix;
    }

    if (prefix != NULL) {
        parsed_url.netloc = strdup(url + strlen(prefix));
        char *slash = strchr(parsed_url.netloc, '/');
        if (slash != NULL) {
            *slash = '\0';
        }
    } else {
        parsed_url.netloc = strdup(url);
    }

    return &parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl *parsed_url = urlparse(url);
    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
}

int main() {
    redirect_url("http://example.com/path/to/resource");
    redirect_url("https://notexample.com/path/to/resource");
    return 0;
}