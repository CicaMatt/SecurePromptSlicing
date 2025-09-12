#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed = {0};
    char *temp = strdup(url);
    char *scheme = strsep(&temp, "://");
    if (scheme && temp) {
        parsed.scheme = strdup(scheme);
        parsed.netloc = temp;
    }
    return parsed;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Not redirecting: domain is not example.com\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char* url1 = "http://example.com";
    const char* url2 = "http://notexample.com";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}