#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {NULL, NULL, NULL};
    const char *p = url;
    const char *end = p + strlen(url);

    // Find the scheme
    while (p < end && *p != ':') p++;
    if (p == end || *(p+1) != '/' || *(p+2) != '/') return parsed_url;
    parsed_url.scheme = strndup(url, p - url);
    p += 3;

    // Find the netloc
    const char *netloc_start = p;
    while (p < end && *p != '/' && *p != '?' && *p != '#') p++;
    parsed_url.netloc = strndup(netloc_start, p - netloc_start);

    // Find the path
    if (*p == '/') {
        const char *path_start = p;
        while (p < end && *p != '?' && *p != '#') p++;
        parsed_url.path = strndup(path_start, p - path_start);
    }

    return parsed_url;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    ParsedURL parsed_url = urlparse(argv[1]);

    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to another URL...\n");
    } else {
        printf("404 Not Found\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);

    return 0;
}