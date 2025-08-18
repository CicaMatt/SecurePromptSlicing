#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {0};
    char *dup = strdup(url);
    char *token = strtok(dup, "://");
    if (token != NULL) {
        parsed_url.scheme = strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed_url.netloc = strdup(token);
        }
    }
    free(dup);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}