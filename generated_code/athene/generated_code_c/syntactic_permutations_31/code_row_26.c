#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = { .scheme = NULL, .netloc = NULL };
    char *buffer = strdup(url);
    char *scheme = strtok(buffer, "://");
    if (scheme) {
        parsed_url.scheme = scheme;
        char *netloc = strtok(NULL, "/");
        if (netloc) {
            parsed_url.netloc = netloc;
        }
    }
    free(buffer);
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error 404: Not Found\n");
    }
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://notexample.com/path");
    return 0;
}