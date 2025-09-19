#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse since it's not available in standard C
typedef struct {
    char scheme[10];
    char netloc[50];
    char path[100];
} UrlParts;

void urlparse(const char *url, UrlParts *parts) {
    const char *scheme_end = strstr(url, "://");
    if (scheme_end != NULL) {
        strncpy(parts->scheme, url, scheme_end - url);
        parts->scheme[scheme_end - url] = '\0';

        const char *path_start = scheme_end + 3;
        const char *netloc_end = strchr(path_start, '/');
        if (netloc_end != NULL) {
            strncpy(parts->netloc, path_start, netloc_end - path_start);
            parts->netloc[netloc_end - path_start] = '\0';
            strcpy(parts->path, netloc_end + 1);
        } else {
            strcpy(parts->netloc, path_start);
            parts->path[0] = '\0';
        }
    } else {
        parts->scheme[0] = '\0';
        parts->netloc[0] = '\0';
        strcpy(parts->path, url);
    }
}

void redirect_url(const char *url) {
    UrlParts parts;
    urlparse(url, &parts);

    printf("Redirecting to: %s://%s/%s\n", parts.scheme, parts.netloc, parts.path);
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}