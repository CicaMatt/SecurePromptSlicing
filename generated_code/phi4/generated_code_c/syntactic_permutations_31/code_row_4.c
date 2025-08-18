#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed;
    char *url_copy = strdup(url);

    if (!strchr(url_copy, ':') || !strstr(url_copy, "//")) {
        free(url_copy);
        return (ParsedURL){NULL, NULL, NULL, NULL, NULL, NULL};
    }

    char *scheme_end = strstr(url_copy + 3, "://");
    parsed.scheme = strndup(url_copy, scheme_end - url_copy);

    char *netloc_start = scheme_end + 3;
    char *path_start = strchr(netloc_start, '/');
    if (path_start) {
        size_t netloc_len = path_start - netloc_start;
        parsed.netloc = strndup(netloc_start, netloc_len);
        parsed.path = strdup(path_start);
    } else {
        parsed.netloc = strdup(netloc_start);
        parsed.path = "";
    }

    free(url_copy);

    return parsed;
}

void handle_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found: The domain is not example.com\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    handle_url(argv[1]);

    return EXIT_SUCCESS;
}