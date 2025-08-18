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
    ParsedURL *parsed_url = (ParsedURL*)malloc(sizeof(ParsedURL));
    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        parsed_url->scheme = strndup(url, scheme_end - url);
        scheme_end += 3;
        const char *path_start = strchr(scheme_end, '/');
        if (path_start) {
            parsed_url->netloc = strndup(scheme_end, path_start - scheme_end);
            parsed_url->path = strdup(path_start);
        } else {
            parsed_url->netloc = strdup(scheme_end);
            parsed_url->path = strdup("");
        }
    } else {
        parsed_url->scheme = strdup("http");
        const char *path_start = strchr(url, '/');
        if (path_start) {
            parsed_url->netloc = strndup(url, path_start - url);
            parsed_url->path = strdup(path_start);
        } else {
            parsed_url->netloc = strdup(url);
            parsed_url->path = strdup("");
        }
    }
    parsed_url->params = strdup("");
    parsed_url->query = strdup("");
    parsed_url->fragment = strdup("");
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
    free(parsed_url->params);
    free(parsed_url->query);
    free(parsed_url->fragment);
    free(parsed_url);
}

int redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
        free_parsed_url(parsed_url);
        return 1;
    } else {
        printf("404 Not Found\n");
        free_parsed_url(parsed_url);
        return 0;
    }
}

int main() {
    const char *url = "http://example.com/some/path";
    redirect_url(url);

    url = "http://notexample.com/some/path";
    redirect_url(url);

    return 0;
}