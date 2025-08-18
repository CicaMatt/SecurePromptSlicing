#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simple URL parsing function for demonstration purposes
typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL* urlparse(const char *url) {
    ParsedURL *parsed_url = (ParsedURL*)malloc(sizeof(ParsedURL));
    parsed_url->scheme = NULL;
    parsed_url->netloc = NULL;
    parsed_url->path = NULL;

    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        size_t scheme_len = scheme_end - url;
        parsed_url->scheme = strndup(url, scheme_len);

        const char *path_start = strchr(scheme_end + 3, '/');
        if (path_start) {
            size_t netloc_len = path_start - (scheme_end + 3);
            parsed_url->netloc = strndup(scheme_end + 3, netloc_len);
            parsed_url->path = strdup(path_start);
        } else {
            parsed_url->netloc = strdup(scheme_end + 3);
        }
    }

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

    const char *redirect_target = "http://newexample.com";
    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        return redirect_target;
    } else {
        return "404 Not Found";
    }

    free_parsed_url(parsed_url);
}

int main() {
    const char *url1 = "http://example.com/somepath";
    const char *url2 = "http://notexample.com/otherpath";

    printf("URL: %s -> Result: %s\n", url1, redirect_url(url1));
    printf("URL: %s -> Result: %s\n", url2, redirect_url(url2));

    return 0;
}