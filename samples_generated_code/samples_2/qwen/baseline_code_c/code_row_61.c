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

ParsedURL* urlparse(const char *url) {
    ParsedURL *parsed_url = malloc(sizeof(ParsedURL));
    parsed_url->netloc = NULL;

    const char *start = strstr(url, "://");
    if (start != NULL) {
        start += 3;
        const char *end = strchr(start, '/');
        size_t len = end ? (size_t)(end - start) : strlen(start);
        parsed_url->netloc = strndup(start, len);
    }

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url != NULL) {
        free(parsed_url->netloc);
        free(parsed_url);
    }
}

const char* redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    const char *result;

    if (parsed_url != NULL && parsed_url->netloc != NULL && strcmp(parsed_url->netloc, "example.com") == 0) {
        result = "Redirected to example.com";
    } else {
        result = "404 Not Found";
    }

    free_parsed_url(parsed_url);
    return result;
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://notexample.com/path";

    printf("%s\n", redirect_url(url1));
    printf("%s\n", redirect_url(url2));

    return 0;
}