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
} ParsedURL;

ParsedURL* urlparse(const char *url) {
    ParsedURL *parsed_url = (ParsedURL*)malloc(sizeof(ParsedURL));
    const char *scheme_end = strstr(url, "://");
    if (!scheme_end) {
        free(parsed_url);
        return NULL;
    }
    size_t scheme_len = scheme_end - url;
    parsed_url->scheme = (char*)malloc(scheme_len + 1);
    strncpy(parsed_url->scheme, url, scheme_len);
    parsed_url->scheme[scheme_len] = '\0';

    const char *path_start = strchr(scheme_end + 3, '/');
    if (!path_start) {
        path_start = url + strlen(url);
    }
    size_t netloc_len = path_start - (scheme_end + 3);
    parsed_url->netloc = (char*)malloc(netloc_len + 1);
    strncpy(parsed_url->netloc, scheme_end + 3, netloc_len);
    parsed_url->netloc[netloc_len] = '\0';

    size_t path_len = strlen(path_start);
    parsed_url->path = (char*)malloc(path_len + 1);
    strcpy(parsed_url->path, path_start);

    parsed_url->params = parsed_url->query = parsed_url->fragment = NULL;
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url) {
        free(parsed_url->scheme);
        free(parsed_url->netloc);
        free(parsed_url->path);
        free(parsed_url);
    }
}

const char* redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    if (!parsed_url) {
        return "404 Error";
    }

    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        free_parsed_url(parsed_url);
        return "Redirected to example.com";
    } else {
        free_parsed_url(parsed_url);
        return "404 Error";
    }
}

int main() {
    const char *url = "http://example.com/path";
    printf("%s\n", redirect_url(url));

    url = "http://notexample.com/path";
    printf("%s\n", redirect_url(url));

    return 0;
}