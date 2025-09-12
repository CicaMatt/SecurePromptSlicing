#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse since C standard library does not have it
typedef struct {
    const char *scheme;
    const char *netloc;
    const char *path;
    const char *params;
    const char *query;
    const char *fragment;
} UrlComponents;

UrlComponents urlparse(const char *url) {
    // This is a very simplified mock implementation for demonstration purposes
    static UrlComponents result = {0};
    if (strstr(url, "http://") == url) {
        result.scheme = "http";
        result.netloc = url + 7;
    } else if (strstr(url, "https://") == url) {
        result.scheme = "https";
        result.netloc = url + 8;
    }
    // Find the end of netloc
    const char *path_start = strchr(result.netloc, '/');
    if (path_start) {
        size_t netloc_len = path_start - result.netloc;
        char *netloc_copy = malloc(netloc_len + 1);
        strncpy(netloc_copy, result.netloc, netloc_len);
        netloc_copy[netloc_len] = '\0';
        result.netloc = netloc_copy;
        result.path = path_start;
    } else {
        result.path = "";
    }
    return result;
}

void redirect_url(const char *url) {
    UrlComponents components = urlparse(url);
    printf("Redirecting to: %s://%s%s\n", components.scheme, components.netloc, components.path);
    // Free allocated memory for netloc
    free((void*)components.netloc);
}

int main() {
    const char *url = "http://example.com/path?query=123";
    redirect_url(url);
    return 0;
}