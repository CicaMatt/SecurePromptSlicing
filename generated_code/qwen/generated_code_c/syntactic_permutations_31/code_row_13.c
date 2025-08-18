#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} UrlComponents;

UrlComponents urlparse(const char *url) {
    UrlComponents components = {0};
    const char *p = url;
    const char *end = url + strlen(url);

    // Parse scheme
    while (p < end && *p != ':') p++;
    if (p < end && *p == ':') {
        components.scheme = strndup(url, p - url);
        p += 3; // Skip "://"
    }

    // Parse netloc
    const char *start_netloc = p;
    while (p < end && *p != '/' && *p != '?' && *p != '#') p++;
    if (start_netloc < p) {
        components.netloc = strndup(start_netloc, p - start_netloc);
    }

    // Parse path
    const char *start_path = p;
    while (p < end && *p != '?' && *p != '#') p++;
    if (start_path < p) {
        components.path = strndup(start_path, p - start_path);
    }

    // Parse query and fragment are ignored for this example

    return components;
}

void free_url_components(UrlComponents components) {
    free(components.scheme);
    free(components.netloc);
    free(components.path);
}

int redirect_url(const char *url) {
    UrlComponents components = urlparse(url);
    int should_redirect = strcmp(components.netloc, "example.com") == 0;

    free_url_components(components);

    if (should_redirect) {
        printf("Redirecting to: %s\n", url);
        return 1;
    } else {
        printf("404 Not Found\n");
        return 0;
    }
}

int main() {
    const char *test_url = "http://example.com/path?query=string";
    redirect_url(test_url);

    const char *invalid_url = "http://notexample.com/path?query=string";
    redirect_url(invalid_url);

    return 0;
}