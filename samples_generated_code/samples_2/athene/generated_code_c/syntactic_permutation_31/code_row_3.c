#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = { .scheme = NULL, .netloc = NULL };
    const char *prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    } else {
        prefix = "https://";
        if (strncmp(url, prefix, strlen(prefix)) == 0) {
            url += strlen(prefix);
        }
    }

    char *url_copy = strdup(url);
    char *slash = strchr(url_copy, '/');
    if (slash != NULL) {
        *slash = '\0';
    }
    parsed_url.netloc = url_copy;

    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    free(parsed_url->netloc);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    ParsedUrl parsed_url = urlparse(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }

    free_parsed_url(&parsed_url);
    return 0;
}