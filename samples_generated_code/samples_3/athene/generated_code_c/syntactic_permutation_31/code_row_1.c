#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = {NULL, NULL};
    const char *scheme_delim = "://";
    const char *slash_delim = "/";
    
    // Parse scheme
    char *scheme_end = strstr(url, scheme_delim);
    if (scheme_end == NULL) return parsed_url;
    int scheme_len = scheme_end - url;
    parsed_url.scheme = malloc(scheme_len + 1);
    strncpy(parsed_url.scheme, url, scheme_len);
    parsed_url.scheme[scheme_len] = '\0';

    // Parse netloc
    char *netloc_start = scheme_end + strlen(scheme_delim);
    char *path_start = strstr(netloc_start, slash_delim);
    if (path_start == NULL) {
        path_start = netloc_start + strlen(netloc_start);
    }
    int netloc_len = path_start - netloc_start;
    parsed_url.netloc = malloc(netloc_len + 1);
    strncpy(parsed_url.netloc, netloc_start, netloc_len);
    parsed_url.netloc[netloc_len] = '\0';

    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    if (parsed_url->scheme) free(parsed_url->scheme);
    if (parsed_url->netloc) free(parsed_url->netloc);
}

int redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (!parsed_url.netloc) {
        printf("404 Error: Invalid URL\n");
        return 1;
    }

    const char *domain = parsed_url.netloc;

    if (strcmp(domain, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not recognized\n");
    }

    free_parsed_url(&parsed_url);
    return 0;
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}