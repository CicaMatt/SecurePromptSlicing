#include <stdio.h>
#include <string.h>

typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    char host[256];
    sscanf(url, "http://%[^/]", host);
    parsed_url.netloc = strdup(host);
    return parsed_url;
}

void free_parsed_url(ParsedUrl parsed_url) {
    free(parsed_url.netloc);
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free_parsed_url(parsed_url);
}

int main() {
    const char* test_url = "http://example.com";
    redirect_url(test_url);
    return 0;
}