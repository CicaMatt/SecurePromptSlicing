#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} UrlComponents;

UrlComponents urlparse(const char *url) {
    UrlComponents components = {NULL, NULL, NULL, NULL, NULL, NULL};
    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        components.scheme = strndup(url, scheme_end - url);
        const char *path_start = scheme_end + 3;
        const char *path_end = strchr(path_start, '/');
        if (path_end) {
            components.netloc = strndup(path_start, path_end - path_start);
            components.path = strdup(path_end);
        } else {
            components.netloc = strdup(path_start);
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
    char *redirected_url = NULL;
    if (components.scheme && strcmp(components.scheme, "http") == 0) {
        size_t new_length = strlen("https") + strlen(components.netloc) + strlen(components.path) + 1;
        redirected_url = malloc(new_length);
        snprintf(redirected_url, new_length, "https://%s%s", components.netloc, components.path);
    }
    free_url_components(&components);
    return redirected_url;
}

int main() {
    const char *url = "http://example.com/path";
    char *new_url = redirect_url(url);
    if (new_url) {
        printf("Redirected URL: %s\n", new_url);
        free(new_url);
    } else {
        printf("No redirection needed.\n");
    }
    return 0;
}