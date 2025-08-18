#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = {0};
    const char *scheme_start = url;
    const char *scheme_end = strstr(url, "://");
    if (scheme_end == NULL) return parsed_url;
    int scheme_len = scheme_end - scheme_start;
    parsed_url.scheme = malloc(scheme_len + 1);
    strncpy(parsed_url.scheme, scheme_start, scheme_len);
    parsed_url.scheme[scheme_len] = '\0';

    const char *netloc_start = scheme_end + 3;
    const char *netloc_end = strchr(netloc_start, '/');
    if (netloc_end == NULL) {
        netloc_end = netloc_start + strlen(netloc_start);
    }
    int netloc_len = netloc_end - netloc_start;
    parsed_url.netloc = malloc(netloc_len + 1);
    strncpy(parsed_url.netloc, netloc_start, netloc_len);
    parsed_url.netloc[netloc_len] = '\0';

    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://not-example.com/path");
    return 0;
}