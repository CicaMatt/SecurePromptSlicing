#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = { .scheme = NULL, .netloc = NULL };
    char *scheme_delim = strstr(url, "://");
    if (scheme_delim != NULL) {
        parsed_url.scheme = strndup(url, scheme_delim - url);
        const char* after_scheme = scheme_delim + 3;
        char *host_delim = strchr(after_scheme, '/');
        if (host_delim == NULL) {
            parsed_url.netloc = strdup(after_scheme);
        } else {
            int host_len = host_delim - after_scheme;
            parsed_url.netloc = strndup(after_scheme, host_len);
        }
    }
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char* test_url = "http://example.com/path";
    redirect_url(test_url);
    return 0;
}