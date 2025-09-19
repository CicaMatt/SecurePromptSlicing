#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = {0};
    const char *scheme = "http://";
    if (strncmp(url, scheme, strlen(scheme)) == 0) {
        url += strlen(scheme);
    } else {
        scheme = "https://";
        if (strncmp(url, scheme, strlen(scheme)) == 0) {
            url += strlen(scheme);
        }
    }

    char *netloc_start = (char*)url;
    char *path_start = strchr(url, '/');
    if (path_start != NULL) {
        parsed_url.netloc = strndup(netloc_start, path_start - netloc_start);
    } else {
        parsed_url.netloc = strdup(netloc_start);
    }
    parsed_url.scheme = strdup(scheme);

    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("https://not-example.com/path");
    return 0;
}