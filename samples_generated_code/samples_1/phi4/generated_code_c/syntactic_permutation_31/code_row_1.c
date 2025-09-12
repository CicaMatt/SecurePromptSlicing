#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char scheme[8];
    char netloc[256];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *protocol_end = strstr(url, "://");
    if (!protocol_end) return -1;
    
    size_t protocol_len = protocol_end - url;
    strncpy(parsed->scheme, url, protocol_len);
    parsed->scheme[protocol_len] = '\0';

    const char *netloc_start = protocol_end + 3;
    const char *path_start = strstr(netloc_start, "/");
    if (!path_start) path_start = netloc_start + strlen(netloc_start);

    size_t netloc_len = path_start - netloc_start;
    strncpy(parsed->netloc, netloc_start, netloc_len);
    parsed->netloc[netloc_len] = '\0';

    return 0;
}

void redirect_url(const char *url) {
    ParsedURL parsed;
    if (parse_url(url, &parsed) != 0) {
        printf("404 Not Found\n");
        return;
    }

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com/path";
    const char *test_url2 = "https://anotherdomain.com";

    redirect_url(test_url1); // Should print: Redirecting to http://example.com/path
    printf("\n");
    redirect_url(test_url2); // Should print: 404 Not Found

    return 0;
}