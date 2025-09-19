#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed = { .scheme = NULL, .netloc = NULL };
    const char *prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    } else {
        return parsed;
    }
    char *end;
    parsed.scheme = strdup("http");
    end = strchr(url, '/');
    if (end != NULL) {
        parsed.netloc = strndup(url, end - url);
    } else {
        parsed.netloc = strdup(url);
    }
    return parsed;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc == NULL || strcmp(parsed_url.netloc, "example.com") != 0) {
        printf("404 Not Found\n");
    } else {
        printf("Redirecting to %s\n", url);
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com";
    redirect_url(url);
    return 0;
}