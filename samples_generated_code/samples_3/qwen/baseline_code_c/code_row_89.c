#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock implementation of urlparse and related structures
typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} UrlParsed;

UrlParsed* urlparse(const char *url) {
    UrlParsed *parsed_url = malloc(sizeof(UrlParsed));
    // Simple parsing logic for demonstration purposes
    parsed_url->scheme = strdup("http");
    if (strstr(url, "://")) {
        parsed_url->netloc = strdup(strstr(url, "://") + 3);
        char *path_start = strchr(parsed_url->netloc, '/');
        if (path_start) {
            *path_start = '\0';
            parsed_url->path = strdup(path_start + 1);
        } else {
            parsed_url->path = strdup("");
        }
    } else {
        parsed_url->netloc = strdup(url);
        parsed_url->path = strdup("");
    }
    parsed_url->params = strdup("");
    parsed_url->query = strdup("");
    parsed_url->fragment = strdup("");
    return parsed_url;
}

void urlparsed_free(UrlParsed *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
    free(parsed_url->params);
    free(parsed_url->query);
    free(parsed_url->fragment);
    free(parsed_url);
}

const char* redirect_url(const char *url) {
    UrlParsed *parsed_url = urlparse(url);
    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        urlparsed_free(parsed_url);
        return "http://new.example.com";
    } else {
        urlparsed_free(parsed_url);
        return "404 Not Found";
    }
}

int main() {
    const char *url1 = "http://example.com/somepath";
    const char *url2 = "http://notexample.com/anotherpath";

    printf("Redirecting %s to %s\n", url1, redirect_url(url1));
    printf("Redirecting %s to %s\n", url2, redirect_url(url2));

    return 0;
}