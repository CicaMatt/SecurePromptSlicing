#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse and related structures
typedef struct {
    char *netloc;
} UrlParsed;

UrlParsed* urlparse(const char *url) {
    static UrlParsed result;
    // Simple parsing for demonstration, does not handle all cases
    const char *prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    }
    size_t end = strcspn(url, "/");
    char *netloc = malloc(end + 1);
    strncpy(netloc, url, end);
    netloc[end] = '\0';
    result.netloc = netloc;
    return &result;
}

void free_parsed_url(UrlParsed* parsed) {
    free(parsed->netloc);
}

int redirect_url(const char *url) {
    UrlParsed *parsed = urlparse(url);
    if (strcmp(parsed->netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
        // Simulate redirection
        return 302;
    } else {
        printf("404 Not Found\n");
        return 404;
    }
    free_parsed_url(parsed);
}

int main() {
    const char *test_url1 = "http://example.com/path";
    const char *test_url2 = "http://notexample.com/path";
    
    redirect_url(test_url1);
    redirect_url(test_url2);

    return 0;
}