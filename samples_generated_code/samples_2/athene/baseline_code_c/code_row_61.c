#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    char *temp = strdup(url);
    char *scheme_end = strchr(temp, ':');
    if (scheme_end) {
        *scheme_end = '\0';
        parsed_url.scheme = strdup(temp);
        temp = scheme_end + 3; // Skip "://"
    } else {
        parsed_url.scheme = strdup("");
    }

    char *path_start = strchr(temp, '/');
    if (path_start) {
        *path_start = '\0';
        parsed_url.netloc = strdup(temp);
        parsed_url.path = strdup(path_start);
    } else {
        parsed_url.netloc = strdup(temp);
        parsed_url.path = strdup("");
    }

    free(temp);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}