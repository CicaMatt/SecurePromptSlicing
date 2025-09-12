#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed = {0};
    char* temp = strdup(url);
    char* scheme = strtok(temp, "://");
    if (scheme && strcmp(scheme, "http") == 0 || strcmp(scheme, "https") == 0) {
        char* rest = strtok(NULL, "/");
        if (rest) {
            parsed.scheme = strdup(scheme);
            parsed.netloc = strdup(rest);
        }
    }
    free(temp);
    return parsed;
}

void free_parsed_url(ParsedUrl* parsed) {
    if (parsed->scheme) free(parsed->scheme);
    if (parsed->netloc) free(parsed->netloc);
}

int redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
        free_parsed_url(&parsed_url);
        return 200;
    } else {
        free_parsed_url(&parsed_url);
        printf("404 Not Found\n");
        return 404;
    }
}

int main() {
    const char* test_url = "http://example.com";
    redirect_url(test_url);
    return 0;
}