#include <stdio.h>
#include <string.h>

typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    char* domain = strstr(url, "//") + 2;
    if (strchr(domain, '/') != NULL) {
        *strchr(domain, '/') = '\0';
    }
    parsed_url.netloc = domain;
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://notexample.com/path");
    return 0;
}