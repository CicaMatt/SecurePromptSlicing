#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    const char *scheme = "http://";
    if (strncmp(url, scheme, strlen(scheme)) == 0) {
        url += strlen(scheme);
    } else {
        scheme = "https://";
        if (strncmp(url, scheme, strlen(scheme)) == 0) {
            url += strlen(scheme);
        }
    }
    parsed_url.scheme = strdup(scheme);

    char* slash_pos = strchr(url, '/');
    if (slash_pos != NULL) {
        size_t len = slash_pos - url;
        parsed_url.netloc = strndup(url, len);
    } else {
        parsed_url.netloc = strdup(url);
    }

    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Not redirecting: %s\n", url);
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char* test_url = "http://example.com/path";
    redirect_url(test_url);

    const char* test_url2 = "https://not-example.com/path";
    redirect_url(test_url2);

    return 0;
}