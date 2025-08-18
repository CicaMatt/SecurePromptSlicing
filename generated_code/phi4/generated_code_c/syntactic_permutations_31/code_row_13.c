#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 2048

typedef struct {
    char scheme[16];
    char netloc[256];
    char path[512];
} ParsedUrl;

void parse_url(const char *url, ParsedUrl *parsed) {
    const char *s = url;
    int i = 0;

    // Parse scheme
    while (*s && !strchr(":/", *s)) {
        parsed->scheme[i++] = *s++;
    }
    parsed->scheme[i] = '\0';

    // Skip "://"
    if (strncmp(s, "://", 3) == 0) s += 3;

    // Parse netloc
    i = 0;
    while (*s && !strchr("/?#", *s)) {
        parsed->netloc[i++] = *s++;
    }
    parsed->netloc[i] = '\0';
}

void redirect_url(const char *url) {
    ParsedUrl parsed;

    parse_url(url, &parsed);

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
}

int main() {
    const char *url1 = "http://example.com/path/to/resource";
    const char *url2 = "https://anotherdomain.com";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}