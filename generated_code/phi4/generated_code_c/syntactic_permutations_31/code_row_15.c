#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL result;
    const char *p = url;
    
    // Extract scheme
    result.scheme = malloc(256);
    int i = 0;
    while (*p != ':' && *p != '\0') {
        result.scheme[i++] = *p++;
    }
    result.scheme[i] = '\0';
    p += 2; // Skip "://"

    // Extract netloc
    result.netloc = malloc(256);
    i = 0;
    while (*p != '/' && *p != '\0') {
        result.netloc[i++] = *p++;
    }
    result.netloc[i] = '\0';

    return result;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    
    printf("Network location: %s\n", parsed_url.netloc);

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *test_url = "http://example.com/path/to/resource";
    redirect_url(test_url);

    return 0;
}