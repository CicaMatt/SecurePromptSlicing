#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        size_t scheme_len = scheme_end - url;
        parsed_url->scheme = strndup(url, scheme_len);
        url = scheme_end + 3; // Move past "://"
    } else {
        parsed_url->scheme = strdup("");
    }

    const char *path_start = strchr(url, '/');
    if (path_start) {
        size_t netloc_len = path_start - url;
        parsed_url->netloc = strndup(url, netloc_len);
        url = path_start; // Move to the start of the path
    } else {
        parsed_url->netloc = strdup(url);
        url = ""; // No path found
    }

    parsed_url->path = strdup(url);
    parsed_url->params = strdup("");
    parsed_url->query = strdup("");
    parsed_url->fragment = strdup("");

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url) {
        free(parsed_url->scheme);
        free(parsed_url->netloc);
        free(parsed_url->path);
        free(parsed_url->params);
        free(parsed_url->query);
        free(parsed_url->fragment);
        free(parsed_url);
    }
}

int redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    if (!parsed_url) return 1; // Error

    int should_redirect = strcmp(parsed_url->netloc, "example.com") == 0;

    free_parsed_url(parsed_url);

    if (should_redirect) {
        printf("Redirecting to: %s\n", url);
        return 0;
    } else {
        printf("404 Not Found\n");
        return 1;
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);

    const char *invalid_url = "http://notexample.com/path";
    redirect_url(invalid_url);

    return 0;
}