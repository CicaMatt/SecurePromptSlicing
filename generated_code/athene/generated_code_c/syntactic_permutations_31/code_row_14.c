#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed = {0};
    char *str = strdup(url);
    char *token = strtok(str, "://");
    if (token != NULL) {
        parsed.scheme = strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed.netloc = strdup(token);
            parsed.path = strndup(str + strlen(parsed.scheme) + strlen("://") + strlen(parsed.netloc), 1024);
        }
    }
    free(str);
    return parsed;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    printf("%s\n", parsed_url.netloc);
    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);
}

int main() {
    const char *url = "http://example.com/path/to/page";
    redirect_url(url);
    return 0;
}