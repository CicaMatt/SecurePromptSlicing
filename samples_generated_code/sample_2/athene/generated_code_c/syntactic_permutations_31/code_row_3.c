#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url;
    char *url_copy = strdup(url);
    char *token = strtok(url_copy, "://");
    if (token != NULL) {
        parsed_url.scheme = token;
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed_url.netloc = token;
        } else {
            parsed_url.netloc = "";
        }
    } else {
        parsed_url.scheme = "";
        parsed_url.netloc = url_copy;
    }
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
    free((void *)parsed_url.scheme);
    free((void *)parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}