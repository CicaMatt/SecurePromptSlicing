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
    parsed_url->scheme = NULL;
    parsed_url->netloc = NULL;
    parsed_url->path = NULL;
    parsed_url->params = NULL;
    parsed_url->query = NULL;
    parsed_url->fragment = NULL;

    const char *start = url;
    const char *end = strstr(start, "://");
    if (end) {
        size_t len = end - start;
        parsed_url->scheme = (char*)malloc(len + 1);
        strncpy(parsed_url->scheme, start, len);
        parsed_url->scheme[len] = '\0';

        start = end + 3;
        end = strchr(start, '/');
        if (!end) {
            end = url + strlen(url);
        }
        len = end - start;
        parsed_url->netloc = (char*)malloc(len + 1);
        strncpy(parsed_url->netloc, start, len);
        parsed_url->netloc[len] = '\0';
    }

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url) {
        free(parsed_url->scheme);
        free(parsed_url->netloc);
        free(parsed_url->path);
        free(parsed_url->params);
        free(parsed_url->query);
        free(parsed_url->fragment);
        free(parsed_url);
    }
}

const char* redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    const char *result;

    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        result = "Redirected to example.com";
    } else {
        result = "404 Not Found";
    }

    free_parsed_url(parsed_url);
    return result;
}

int main() {
    const char *url1 = "http://example.com/some/path?query=123#fragment";
    const char *url2 = "http://anotherdomain.com";

    printf("%s\n", redirect_url(url1));
    printf("%s\n", redirect_url(url2));

    return 0;
}