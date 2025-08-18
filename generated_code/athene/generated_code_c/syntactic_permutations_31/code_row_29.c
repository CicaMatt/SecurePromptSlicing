#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    const char* scheme_delim = "://";
    const char* path_delim = "/";
    
    // Extract scheme
    char* scheme_end = strstr(url, scheme_delim);
    if (scheme_end == NULL) {
        parsed_url.scheme = NULL;
        parsed_url.netloc = NULL;
        return parsed_url;
    }
    int scheme_len = scheme_end - url;
    parsed_url.scheme = malloc(scheme_len + 1);
    strncpy(parsed_url.scheme, url, scheme_len);
    parsed_url.scheme[scheme_len] = '\0';
    
    // Extract netloc
    const char* path_start = strstr(url, path_delim);
    if (path_start == NULL) {
        int netloc_len = strlen(url) - (scheme_len + 3);
        parsed_url.netloc = malloc(netloc_len + 1);
        strncpy(parsed_url.netloc, scheme_end + 3, netloc_len);
        parsed_url.netloc[netloc_len] = '\0';
    } else {
        int netloc_len = path_start - (scheme_end + 3);
        parsed_url.netloc = malloc(netloc_len + 1);
        strncpy(parsed_url.netloc, scheme_end + 3, netloc_len);
        parsed_url.netloc[netloc_len] = '\0';
    }
    
    return parsed_url;
}

const char* redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.scheme == NULL || parsed_url.netloc == NULL) {
        return "Invalid URL";
    }

    const char* domain = parsed_url.netloc;

    if (strcmp(domain, "example.com") == 0) {
        free(parsed_url.scheme);
        free(parsed_url.netloc);
        return "https://example.com/redirected";
    } else {
        free(parsed_url.scheme);
        free(parsed_url.netloc);
        return url;
    }
}

int main() {
    const char* url = "http://example.com/path?query=value";
    printf("%s\n", redirect_url(url));
    return 0;
}