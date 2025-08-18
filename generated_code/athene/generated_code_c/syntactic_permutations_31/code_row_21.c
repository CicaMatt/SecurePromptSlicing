#include <stdio.h>
#include <string.h>

typedef struct {
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url;
    char netloc[256];
    sscanf(url, "http://%[^/]", netloc);
    parsed_url.netloc = strdup(netloc);
    return parsed_url;
}

int redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
        free(parsed_url.netloc);
        return 302; // Redirect status code
    } else {
        free(parsed_url.netloc);
        return 404; // Not Found status code
    }
}

int main() {
    const char *url = "http://example.com/path";
    int result = redirect_url(url);
    if (result == 404) {
        printf("Error: Page not found\n");
    }
    return 0;
}