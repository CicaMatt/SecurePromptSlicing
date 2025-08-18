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

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free(parsed_url.netloc);
}

int main() {
    const char* url = "http://example.com/path";
    redirect_url(url);
    return 0;
}