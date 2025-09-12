#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed = { .scheme = NULL, .netloc = NULL };
    char *dup_url = strdup(url);
    char *token = strtok(dup_url, "://");
    if (token != NULL) {
        parsed.scheme = token;
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed.netloc = token;
        }
    }
    free(dup_url);
    return parsed;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}