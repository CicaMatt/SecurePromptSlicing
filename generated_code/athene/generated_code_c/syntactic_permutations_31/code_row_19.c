#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = { .scheme = NULL, .netloc = NULL };
    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        size_t scheme_len = scheme_end - url;
        parsed_url.scheme = malloc(scheme_len + 1);
        strncpy(parsed_url.scheme, url, scheme_len);
        parsed_url.scheme[scheme_len] = '\0';
        
        const char *netloc_start = scheme_end + 3; // Length of "://"
        const char *netloc_end = strchr(netloc_start, '/');
        if (netloc_end) {
            size_t netloc_len = netloc_end - netloc_start;
            parsed_url.netloc = malloc(netloc_len + 1);
            strncpy(parsed_url.netloc, netloc_start, netloc_len);
            parsed_url.netloc[netloc_len] = '\0';
        } else {
            parsed_url.netloc = strdup(netloc_start);
        }
    }
    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    if (parsed_url->scheme) free(parsed_url->scheme);
    if (parsed_url->netloc) free(parsed_url->netloc);
}

int redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
        free_parsed_url(&parsed_url);
        return 302; // HTTP status code for Found (redirect)
    } else {
        printf("404 Not Found\n");
        free_parsed_url(&parsed_url);
        return 404; // HTTP status code for Not Found
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}