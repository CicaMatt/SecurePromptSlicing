#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

typedef struct {
    char scheme[16];
    char netloc[256];
    char path[MAX_URL_LENGTH];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *at = strstr(url, "://");
    if (at == NULL) return 0;
    
    strncpy(parsed->scheme, url, at - url);
    parsed->scheme[at - url] = '\0';

    const char *start_netloc = at + 3; // skip "://"
    const char *end_netloc = strchr(start_netloc, '/');
    if (end_netloc == NULL) end_netloc = start_netloc + strlen(start_netloc);

    strncpy(parsed->netloc, start_netloc, end_netloc - start_netloc);
    parsed->netloc[end_netloc - start_netloc] = '\0';

    const char *path_start = end_netloc;
    strcpy(parsed->path, path_start);

    return 1;
}

void redirect_url(const char *url) {
    ParsedURL parsed;
    if (!parse_url(url, &parsed)) {
        fprintf(stderr, "Invalid URL\n");
        return;
    }

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Domain is example.com. Redirecting...\n");
    } else {
        printf("Domain is not example.com.\n");
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}