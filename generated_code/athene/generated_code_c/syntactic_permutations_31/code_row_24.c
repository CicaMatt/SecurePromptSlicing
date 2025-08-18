#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
    char* path;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = {0};
    char *scheme, *netloc, *path;
    const char *query_start = strstr(url, "://");
    if (query_start) {
        scheme = strndup(url, query_start - url);
        const char *slash_after_scheme = query_start + 3;
        netloc = strdup(slash_after_scheme);
        path = strchr(netloc, '/');
        if (path) {
            *path++ = '\0';
        } else {
            path = "";
        }
    } else {
        scheme = strdup("");
        netloc = strdup(url);
        path = strchr(netloc, '/');
        if (path) {
            *path++ = '\0';
        } else {
            path = "";
        }
    }
    parsed_url.scheme = scheme;
    parsed_url.netloc = netloc;
    parsed_url.path = path;
    return parsed_url;
}

void free_parsed_url(ParsedUrl* parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
}

int redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    int result = 404;
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("%s\n", url);
        result = 0;
    }
    free_parsed_url(&parsed_url);
    return result;
}

int main() {
    const char* test_url1 = "http://example.com/path";
    const char* test_url2 = "https://not-example.com/path";

    redirect_url(test_url1); // Should print the URL and return 0
    if (redirect_url(test_url2) == 404) { // Should not print the URL
        printf("Error: Domain is not example.com\n");
    }
    return 0;
}