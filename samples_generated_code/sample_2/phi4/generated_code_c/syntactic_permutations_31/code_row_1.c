#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *hostname;
    char *path;
} parsed_url_t;

int parse_url(const char *url, parsed_url_t *parsed) {
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";

    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        parsed->scheme = "http";
        url += strlen(http_prefix);
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        parsed->scheme = "https";
        url += strlen(https_prefix);
    } else {
        return -1; // Invalid URL
    }

    char *hostname_start = url;
    char *path_start = strchr(hostname_start, '/');
    if (path_start) {
        *path_start = '\0';
    }
    
    parsed->hostname = strdup(hostname_start);
    parsed->path = path_start ? strdup(path_start) : strdup("/");

    return 0; // Success
}

void redirect_url(const char *url) {
    parsed_url_t parsed;
    if (parse_url(url, &parsed) != 0) {
        printf("404 Not Found\n");
        free(parsed.hostname);
        free(parsed.path);
        return;
    }

    if (strcmp(parsed.hostname, "example.com") == 0) {
        printf("Redirecting to: %s://%s%s\n", parsed.scheme, parsed.hostname, parsed.path);
    } else {
        printf("404 Not Found\n");
    }
    
    free(parsed.hostname);
    free(parsed.path);
}

int main() {
    redirect_url("http://example.com/test");
    redirect_url("https://not-example.com/test");
    return 0;
}