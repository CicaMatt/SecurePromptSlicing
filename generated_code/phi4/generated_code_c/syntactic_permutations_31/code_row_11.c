#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url;
    const char *delimiter = "://";
    
    // Extract scheme and netloc
    char *start = strstr(url, delimiter);
    if (start == NULL) return parsed_url;  // Invalid URL format

    int scheme_len = start - url;
    parsed_url.scheme = strndup(url, scheme_len);

    start += strlen(delimiter);  // Move past the delimiter to the netloc part
    char *end = strchr(start, '/');
    
    if (end == NULL) {
        parsed_url.netloc = strdup(start);
    } else {
        int netloc_len = end - start;
        parsed_url.netloc = strndup(start, netloc_len);
    }
    
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);

    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not allowed.\n");
    }
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "https://not-example.com/path";

    redirect_url(url1);  // Should redirect
    redirect_url(url2);  // Should return a 404 error

    return 0;
}