#include <stdio.h>
#include <string.h>

typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    char buffer[256];
    sscanf(url, "http://%[^/]", buffer);
    parsed_url.netloc = strdup(buffer);
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Domain not allowed: %s\n", parsed_url.netloc);
    }
    free(parsed_url.netloc);
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://notexample.com/path");
    return 0;
}