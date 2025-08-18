#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {0};
    char *dup = strdup(url);
    char *scheme_end = strchr(dup, ':');
    if (scheme_end) {
        *scheme_end = '\0';
        parsed_url.scheme = strdup(dup);
        dup = scheme_end + 3; // Skip "://"
    } else {
        parsed_url.scheme = strdup("");
    }

    char *netloc_start = dup;
    char *path_start = strchr(dup, '/');
    if (path_start) {
        *path_start = '\0';
        netloc_start = strdup(dup);
    } else {
        netloc_start = strdup(dup);
    }
    parsed_url.netloc = netloc_start;

    free(dup);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}