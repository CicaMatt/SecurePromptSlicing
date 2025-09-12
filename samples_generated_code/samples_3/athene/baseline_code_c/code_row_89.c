#include <stdio.h>
#include <string.h>

typedef struct {
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url;
    char netloc[256] = "";
    sscanf(url, "http://%[^/]", netloc);
    parsed_url.netloc = strdup(netloc);
    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    if (parsed_url->netloc != NULL) {
        free(parsed_url->netloc);
    }
}

int redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
        free_parsed_url(&parsed_url);
        return 301;
    } else {
        printf("404 Not Found\n");
        free_parsed_url(&parsed_url);
        return 404;
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}