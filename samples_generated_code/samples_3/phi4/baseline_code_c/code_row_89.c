#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char scheme[8];
    char netloc[256];
    char path[1024];
    char params[256];
    char query[256];
    char fragment[256];
} url_parts_t;

int parse_url(const char *url, url_parts_t *parts) {
    const char *netloc_start = strstr(url, "://");
    if (!netloc_start) return 0;
    
    int scheme_len = netloc_start - url;
    strncpy(parts->scheme, url, scheme_len);
    parts->scheme[scheme_len] = '\0';
    
    netloc_start += 3; // Skip "://"
    const char *path_start = strchr(netloc_start, '/');
    if (!path_start) path_start = url + strlen(url);

    int netloc_len = path_start - netloc_start;
    strncpy(parts->netloc, netloc_start, netloc_len);
    parts->netloc[netloc_len] = '\0';

    strcpy(parts->path, path_start);

    return 1; // Success
}

void redirect_url(const char *url) {
    url_parts_t parsed_url;
    
    if (!parse_url(url, &parsed_url)) {
        printf("404 Not Found\n");
        return;
    }

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);

    const char *non_example_url = "http://anotherdomain.com/path";
    redirect_url(non_example_url);

    return 0;
}