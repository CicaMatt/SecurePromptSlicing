#include <stdio.h>
#include <string.h>

typedef struct {
    const char *scheme;
    const char *netloc;
    const char *path;
    const char *params;
    const char *query;
    const char *fragment;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        parsed_url.scheme = strndup(url, scheme_end - url);
        const char *path_start = strchr(scheme_end + 3, '/');
        if (path_start) {
            parsed_url.netloc = strndup(scheme_end + 3, path_start - (scheme_end + 3));
        } else {
            parsed_url.netloc = strdup(scheme_end + 3);
        }
    }
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free((void*)parsed_url.scheme);
    free((void*)parsed_url.netloc);
}

int main() {
    redirect_url("http://example.com/path/to/resource");
    redirect_url("http://notexample.com/path/to/resource");
    return 0;
}