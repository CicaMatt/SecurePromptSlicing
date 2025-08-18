#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse for demonstration purposes
typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *start = strstr(url, "://") + 3;
    const char *end = strchr(start, '/');
    size_t len = end - start;

    parsed_url.scheme = strdup("http"); // Simplified for example
    parsed_url.netloc = strndup(start, len);
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
    free(parsed_url->params);
    free(parsed_url->query);
    free(parsed_url->fragment);
}

int redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    int result = strcmp(parsed_url.netloc, "example.com") == 0;
    free_parsed_url(&parsed_url);
    return result;
}

int main() {
    const char *test_url = "http://example.com/path?query=1";
    if (redirect_url(test_url)) {
        printf("Domain is example.com\n");
    } else {
        printf("Domain is not example.com\n");
    }
    return 0;
}