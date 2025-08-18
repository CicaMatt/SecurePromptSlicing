#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse for demonstration purposes
typedef struct {
    const char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed;
    // This is a very simple mock implementation that assumes the URL format
    const char* prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        parsed.netloc = url + strlen(prefix);
    } else {
        parsed.netloc = "";
    }
    return parsed;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
}

int main() {
    const char* test_url1 = "http://example.com";
    const char* test_url2 = "http://notexample.com";

    redirect_url(test_url1);
    redirect_url(test_url2);

    return 0;
}