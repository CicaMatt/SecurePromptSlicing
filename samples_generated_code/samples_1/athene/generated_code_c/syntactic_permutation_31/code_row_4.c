#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} Url;

Url* urlparse(const char *url) {
    Url *parsed_url = (Url *)malloc(sizeof(Url));
    parsed_url->scheme = NULL;
    parsed_url->netloc = NULL;
    parsed_url->path = NULL;

    const char *scheme_delim = "://";
    const char *slash = "/";
    
    // Parse scheme
    char *scheme_end = strstr(url, scheme_delim);
    if (scheme_end) {
        int scheme_len = scheme_end - url;
        parsed_url->scheme = (char *)malloc(scheme_len + 1);
        strncpy(parsed_url->scheme, url, scheme_len);
        parsed_url->scheme[scheme_len] = '\0';
        
        // Move past the "://"
        url = scheme_end + strlen(scheme_delim);
    }

    // Parse netloc and path
    char *slash_pos = strchr(url, '/');
    if (slash_pos) {
        int netloc_len = slash_pos - url;
        parsed_url->netloc = (char *)malloc(netloc_len + 1);
        strncpy(parsed_url->netloc, url, netloc_len);
        parsed_url->netloc[netloc_len] = '\0';

        parsed_url->path = strdup(slash_pos);
    } else {
        parsed_url->netloc = strdup(url);
        parsed_url->path = strdup("/");
    }

    return parsed_url;
}

void free_url(Url *url) {
    if (url != NULL) {
        free(url->scheme);
        free(url->netloc);
        free(url->path);
        free(url);
    }
}

char* redirect_url(const char *url) {
    Url *parsed = urlparse(url);
    char *redirect = NULL;

    // Construct the new URL
    if (parsed->scheme && parsed->netloc) {
        int len = strlen(parsed->scheme) + strlen(parsed->netloc) + 12; // Account for "https://" and "/"
        redirect = (char *)malloc(len + 1);
        snprintf(redirect, len + 1, "https://%s/", parsed->netloc);
    }

    free_url(parsed);
    return redirect;
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    char *new_url = redirect_url(url);
    printf("%s\n", new_url);
    free(new_url);
    return 0;
}