#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {NULL, NULL, NULL};
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";

    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        url += strlen(http_prefix);
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        url += strlen(https_prefix);
    }

    const char *path_start = strchr(url, '/');
    if (path_start != NULL) {
        parsed_url.netloc = strndup(url, path_start - url);
        parsed_url.path = strdup(path_start);
    } else {
        parsed_url.netloc = strdup(url);
    }

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url->scheme != NULL) free(parsed_url->scheme);
    if (parsed_url->netloc != NULL) free(parsed_url->netloc);
    if (parsed_url->path != NULL) free(parsed_url->path);
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    const char *domain_name = parsed_url.netloc;

    if (strcmp(domain_name, "example.com") == 0) { // Replace "example.com" with the actual domain to check
        free_parsed_url(&parsed_url);
        return "Redirected";
    } else {
        free_parsed_url(&parsed_url);
        return "404 Error";
    }
}

int main() {
    const char *url = "http://example.com/some/path";
    printf("%s\n", redirect_url(url));

    url = "http://notfound.com/some/path";
    printf("%s\n", redirect_url(url));

    return 0;
}