#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *host;
    char *path;
} Url;

Url* urlparse(const char *url) {
    Url *parsed_url = (Url *)malloc(sizeof(Url));
    parsed_url->scheme = NULL;
    parsed_url->host = NULL;
    parsed_url->path = NULL;

    const char *scheme_delim = strstr(url, "://");
    if (scheme_delim != NULL) {
        size_t scheme_len = scheme_delim - url;
        parsed_url->scheme = (char *)malloc(scheme_len + 1);
        strncpy(parsed_url->scheme, url, scheme_len);
        parsed_url->scheme[scheme_len] = '\0';
        url = scheme_delim + 3;
    }

    const char *path_delim = strchr(url, '/');
    if (path_delim != NULL) {
        size_t host_len = path_delim - url;
        parsed_url->host = (char *)malloc(host_len + 1);
        strncpy(parsed_url->host, url, host_len);
        parsed_url->host[host_len] = '\0';
        parsed_url->path = strdup(path_delim);
    } else {
        parsed_url->host = strdup(url);
    }

    return parsed_url;
}

void redirect_url(const char *url) {
    Url *parsed = urlparse(url);
    if (parsed != NULL && parsed->scheme != NULL && parsed->host != NULL) {
        printf("Redirecting to: %s://%s\n", parsed->scheme, parsed->host);
    } else {
        printf("Invalid URL\n");
    }

    if (parsed->scheme) free(parsed->scheme);
    if (parsed->host) free(parsed->host);
    if (parsed->path) free(parsed->path);
    free(parsed);
}

int main() {
    const char *url = "https://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}