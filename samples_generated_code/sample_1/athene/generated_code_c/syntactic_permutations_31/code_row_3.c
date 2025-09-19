#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url;
    char *temp = strdup(url);
    char *scheme_end = strchr(temp, ':');
    if (scheme_end == NULL) {
        free(temp);
        exit(EXIT_FAILURE);
    }
    *scheme_end = '\0';
    parsed_url.scheme = temp;
    const char *netloc_start = scheme_end + 3; // Skip "://"
    char *netloc_end = strchr(netloc_start, '/');
    if (netloc_end == NULL) {
        netloc_end = strchr(netloc_start, '\0');
    }
    int len = netloc_end - netloc_start;
    parsed_url.netloc = strndup(netloc_start, len);
    free(temp);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error 404: Not Found\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}