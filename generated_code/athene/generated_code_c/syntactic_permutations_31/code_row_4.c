#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = { .scheme = NULL, .netloc = NULL };
    const char* scheme_delim = "://";
    const char* path_delim = "/";

    char* scheme_start = (char*)url;
    char* scheme_end = strstr(scheme_start, scheme_delim);
    if (scheme_end) {
        parsed_url.scheme = strndup(scheme_start, scheme_end - scheme_start);
        char* netloc_start = scheme_end + strlen(scheme_delim);
        char* path_start = strchr(netloc_start, '/');
        if (path_start) {
            parsed_url.netloc = strndup(netloc_start, path_start - netloc_start);
        } else {
            parsed_url.netloc = strdup(netloc_start);
        }
    }

    return parsed_url;
}

void free_parsed_url(ParsedUrl* parsed_url) {
    if (parsed_url->scheme) free(parsed_url->scheme);
    if (parsed_url->netloc) free(parsed_url->netloc);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    ParsedUrl parsed_url = urlparse(argv[1]);

    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to example.com\n");
    } else {
        printf("404 Not Found\n");
    }

    free_parsed_url(&parsed_url);
    return 0;
}