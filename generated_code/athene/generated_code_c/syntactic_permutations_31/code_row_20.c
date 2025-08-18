#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {0};
    const char *scheme_end = strstr(url, "://");
    if (scheme_end != NULL) {
        size_t scheme_len = scheme_end - url;
        parsed_url.scheme = malloc(scheme_len + 1);
        strncpy(parsed_url.scheme, url, scheme_len);
        parsed_url.scheme[scheme_len] = '\0';
        const char *netloc_start = scheme_end + 3;
        const char *netloc_end = strchr(netloc_start, '/');
        if (netloc_end == NULL) {
            netloc_end = netloc_start + strlen(netloc_start);
        }
        size_t netloc_len = netloc_end - netloc_start;
        parsed_url.netloc = malloc(netloc_len + 1);
        strncpy(parsed_url.netloc, netloc_start, netloc_len);
        parsed_url.netloc[netloc_len] = '\0';
    }
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc + strlen(parsed_url.netloc) - 4, ".com") == 0) {
        printf("Domain is .com: %s\n", parsed_url.netloc);
    } else {
        printf("Domain is not .com\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}