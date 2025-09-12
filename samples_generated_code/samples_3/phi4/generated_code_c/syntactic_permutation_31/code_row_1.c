#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for domains and errors
#define REDIRECT_DOMAIN "example.com"
#define ERROR_404 "404 Not Found"

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} URLComponents;

int parse_url(const char *url, URLComponents *components) {
    const char *delimiters = "://?#";
    char *temp = strdup(url);
    if (!temp) return -1;

    // Parse scheme
    components->scheme = strndup(temp, strcspn(temp, delimiters));
    temp += strcspn(temp, delimiters) + 1;

    // Parse netloc
    components->netloc = strndup(temp, strcspn(temp, "?#"));
    if (components->netloc && *temp == '[') {
        char *end_bracket = strchr(components->netloc + 1, ']');
        if (end_bracket) {
            size_t len = end_bracket - components->netloc;
            components->netloc[len] = '\0';
            temp += strcspn(temp, "]") + 2;
        } else return -1;
    }
    
    // Parse path
    char *path_start = strchr(temp, '/');
    if (path_start) {
        components->path = strdup(path_start);
    } else {
        components->path = strdup("/");
    }

    // Parse query
    char *query_start = strchr(components->path, '?');
    if (query_start) {
        *query_start = '\0';
        components->query = strdup(query_start + 1);
    } else {
        components->query = NULL;
    }
    
    // Parse fragment
    char *fragment_start = strchr(components->path, '#');
    if (fragment_start) {
        *fragment_start = '\0';
        components->fragment = strdup(fragment_start + 1);
    } else {
        components->fragment = NULL;
    }

    free(temp);
    return 0;
}

void redirect_url(const char *url) {
    URLComponents components;
    if (parse_url(url, &components)) {
        printf("%s\n", ERROR_404);
        return;
    }

    if (strcmp(components.netloc, REDIRECT_DOMAIN) == 0) {
        printf("Redirect to %s\n", url);
    } else {
        printf("%s\n", ERROR_404);
    }
    
    // Free allocated memory
    free(components.scheme);
    free(components.netloc);
    free(components.path);
    if (components.query) free(components.query);
    if (components.fragment) free(components.fragment);
}

int main() {
    const char *test_url = "http://example.com/path?query#fragment";
    redirect_url(test_url);

    const char *non_redirect_url = "http://notexample.com/path";
    redirect_url(non_redirect_url);

    return 0;
}