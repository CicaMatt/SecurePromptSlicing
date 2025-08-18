#include <stdio.h>
#include <string.h>

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

    const char *delimiter = "://";
    size_t delim_len = strlen(delimiter);
    if (strncmp(url, delimiter, delim_len) == 0) {
        char *scheme_end = strstr(url + delim_len, delimiter);
        if (scheme_end) {
            parsed_url.scheme = strndup(url, scheme_end - url);
            const char *netloc_start = scheme_end + delim_len;
            char *path_start = strchr(netloc_start, '/');
            if (path_start) {
                parsed_url.netloc = strndup(netloc_start, path_start - netloc_start);
                parsed_url.path = strdup(path_start);
            } else {
                parsed_url.netloc = strdup(netloc_start);
            }
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

    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);
    free(parsed_url.params);
    free(parsed_url.query);
    free(parsed_url.fragment);
}

int main() {
    redirect_url("http://example.com/path/to/resource?query=123#fragment");
    redirect_url("https://notexample.com/anotherpath");

    return 0;
}