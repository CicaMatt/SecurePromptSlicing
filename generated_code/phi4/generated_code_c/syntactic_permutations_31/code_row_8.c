#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char scheme[16];
    char netloc[256];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *netloc_start = strstr(url, "://");
    if (!netloc_start) return -1;
    
    strncpy(parsed->scheme, url, netloc_start - url);
    parsed->scheme[netloc_start - url] = '\0';

    netloc_start += 3; // Skip the "://"
    
    const char *path_start = strchr(netloc_start, '/');
    if (!path_start) path_start = netloc_start + strlen(netloc_start);

    strncpy(parsed->netloc, netloc_start, path_start - netloc_start);
    parsed->netloc[path_start - netloc_start] = '\0';

    return 0;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url;
    
    if (parse_url(url, &parsed_url) != 0) {
        printf("404 Not Found\n");
        return;
    }

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);

    const char *url2 = "http://anotherdomain.com/path/to/resource";
    redirect_url(url2);

    return 0;
}