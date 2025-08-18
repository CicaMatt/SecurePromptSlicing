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
    const char *start, *end;

    // Scheme
    start = url;
    end = strchr(url, ':');
    if (end && *(end + 1) == '/' && *(end + 2) == '/') {
        components.scheme = strndup(start, end - start);
        start = end + 3;
    }

    // Netloc
    end = strchr(start, '/');
    if (!end) {
        components.netloc = strdup(start);
    } else {
        components.netloc = strndup(start, end - start);
        start = end;
    }

    // Path
    end = strchr(start, '?');
    if (!end) {
        components.path = strdup(start);
    } else {
        components.path = strndup(start, end - start);
        start = end + 1;

        // Query
        end = strchr(start, '#');
        if (!end) {
            components.query = strdup(start);
        } else {
            components.query = strndup(start, end - start);
            start = end + 1;

            // Fragment
            components.fragment = strdup(start);
        }
    }

    return components;
}

void free_url_components(UrlComponents *components) {
    free(components->scheme);
    free(components->netloc);
    free(components->path);
    free(components->params);
    free(components->query);
    free(components->fragment);
}

char* redirect_url(const char *url) {
    UrlComponents components = urlparse(url);
    char *redirected_url;

    if (components.scheme && strcmp(components.scheme, "http") == 0) {
        size_t new_url_len = strlen("https") + strlen(components.netloc) + strlen(components.path) +
                             (components.query ? strlen(components.query) : 0) +
                             (components.fragment ? strlen(components.fragment) : 0) + 5;
        redirected_url = malloc(new_url_len);
        snprintf(redirected_url, new_url_len, "https://%s%s%s%s",
                 components.netloc, components.path,
                 components.query ? "?" : "", components.query ? components.query : "",
                 components.fragment ? "#" : "", components.fragment ? components.fragment : "");
    } else {
        redirected_url = strdup(url);
    }

    free_url_components(&components);
    return redirected_url;
}

int main() {
    const char *url = "http://example.com/path?query=123#fragment";
    char *redirected = redirect_url(url);
    printf("Original URL: %s\n", url);
    printf("Redirected URL: %s\n", redirected);
    free(redirected);
    return 0;
}