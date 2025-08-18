#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {NULL, NULL};
    char *temp = strdup(url);
    char *scheme_end = strchr(temp, ':');
    if (scheme_end != NULL) {
        *scheme_end = '\0';
        parsed_url.scheme = strdup(temp);
        char *netloc_start = scheme_end + 3; // Skip "://"
        char *netloc_end = strchr(netloc_start, '/');
        if (netloc_end != NULL) {
            *netloc_end = '\0';
        }
        parsed_url.netloc = strdup(netloc_start);
    }
    free(temp);
    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error 404: Not Found\n");
    }
    free_parsed_url(&parsed_url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }
    redirect_url(argv[1]);
    return 0;
}