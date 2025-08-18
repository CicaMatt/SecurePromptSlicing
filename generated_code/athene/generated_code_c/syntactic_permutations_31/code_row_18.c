#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url;
    char *copy = strdup(url);
    char *scheme = strtok(copy, "://");
    if (scheme == NULL) {
        free(copy);
        parsed_url.scheme = "";
        parsed_url.netloc = "";
        return parsed_url;
    }
    char *rest = strtok(NULL, "");
    char *netloc = strndup(rest, strcspn(rest, "/"));
    parsed_url.scheme = strdup(scheme);
    parsed_url.netloc = netloc;
    free(copy);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strlen(parsed_url.netloc) > 0) {
        printf("Domain: %s\n", parsed_url.netloc);
    } else {
        printf("Invalid URL or no domain found.\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "https://www.example.com/path/to/resource";
    redirect_url(url);
    return 0;
}