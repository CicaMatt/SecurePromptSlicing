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
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        size_t scheme_len = scheme_end - url;
        parsed_url.scheme = strndup(url, scheme_len);
        const char *path_start = strchr(scheme_end + 3, '/');
        if (path_start) {
            size_t netloc_len = path_start - (scheme_end + 3);
            parsed_url.netloc = strndup(scheme_end + 3, netloc_len);
        } else {
            parsed_url.netloc = strdup(scheme_end + 3);
        }
    }
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
    free(parsed_url->params);
    free(parsed_url->query);
    free(parsed_url->fragment);
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Not redirecting: %s\n", url);
    }
    free_parsed_url(&parsed_url);
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}