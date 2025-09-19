#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {0};
    char *scheme, *netloc;
    char *url_copy = strdup(url);
    
    scheme = strtok(url_copy, "://");
    netloc = strtok(NULL, "/");
    
    if (scheme && netloc) {
        parsed_url.scheme = scheme;
        parsed_url.netloc = netloc;
    }
    
    free(url_copy);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Domain is not example.com, no redirect.\n");
    }
    
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}