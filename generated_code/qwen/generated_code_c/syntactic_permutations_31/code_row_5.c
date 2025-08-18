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
    const char *start, *end;

    // Find scheme
    start = url;
    end = strchr(url, ':');
    if (end) {
        parsed_url.scheme = strndup(start, end - start);
    }

    // Find netloc
    start = strstr(url, "//");
    if (start) {
        start += 2;
        end = strchr(start, '/');
        if (!end) {
            end = url + strlen(url);
        }
        parsed_url.netloc = strndup(start, end - start);
    }

    // For simplicity, other fields are not parsed
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
        printf("404 Not Found\n");
    }

    free_parsed_url(&parsed_url);
}

int main() {
    const char *url = "http://example.com/some/path";
    redirect_url(url);

    return 0;
}