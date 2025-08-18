#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = {NULL, NULL};
    char* dup_url = strdup(url);
    char* token = strtok(dup_url, "://");
    if (token != NULL) {
        parsed_url.scheme = strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed_url.netloc = strdup(token);
        }
    }
    free(dup_url);
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
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