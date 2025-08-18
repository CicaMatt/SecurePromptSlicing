#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = {0};
    const char* scheme_delim = "://";
    const char* path_delim = "/";

    // Extract scheme
    char* scheme_end = strstr(url, scheme_delim);
    if (scheme_end == NULL) return parsed_url;
    int scheme_len = scheme_end - url;
    parsed_url.scheme = malloc(scheme_len + 1);
    strncpy(parsed_url.scheme, url, scheme_len);
    parsed_url.scheme[scheme_len] = '\0';

    // Extract netloc
    const char* path_start = strstr(url, path_delim);
    if (path_start == NULL) {
        parsed_url.netloc = strdup(scheme_end + strlen(scheme_delim));
    } else {
        int netloc_len = path_start - scheme_end - strlen(scheme_delim);
        parsed_url.netloc = malloc(netloc_len + 1);
        strncpy(parsed_url.netloc, scheme_end + strlen(scheme_delim), netloc_len);
        parsed_url.netloc[netloc_len] = '\0';
    }

    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Domain not recognized\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char* test_url = "http://example.com/path/to/resource";
    redirect_url(test_url);

    return 0;
}