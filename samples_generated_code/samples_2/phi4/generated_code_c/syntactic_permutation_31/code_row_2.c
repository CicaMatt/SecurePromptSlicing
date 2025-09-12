#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";

    ParsedURL parsed;
    parsed.scheme = NULL;
    parsed.netloc = NULL;

    size_t len = strlen(url);

    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        parsed.scheme = strdup("http");
        parsed.netloc = strdup(url + strlen(http_prefix));
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        parsed.scheme = strdup("https");
        parsed.netloc = strdup(url + strlen(https_prefix));
    }

    return parsed;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Not Found\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url1 = "http://example.com";
    const char *url2 = "https://not-example.com";

    redirect_url(url1); // Should redirect
    redirect_url(url2); // Should return 404 error

    return 0;
}