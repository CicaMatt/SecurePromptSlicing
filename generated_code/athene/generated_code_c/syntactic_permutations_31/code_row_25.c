#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char scheme[MAX_URL_LENGTH];
    char netloc[MAX_URL_LENGTH];
} ParsedUrl;

void parse_url(const char *url, ParsedUrl *parsed_url) {
    char *scheme = strtok((char *)url, "://");
    if (scheme != NULL) {
        strncpy(parsed_url->scheme, scheme, MAX_URL_LENGTH - 1);
        const char *netloc_start = url + strlen(scheme) + 3;
        char *netloc = strtok((char *)netloc_start, "/");
        if (netloc != NULL) {
            strncpy(parsed_url->netloc, netloc, MAX_URL_LENGTH - 1);
        }
    }
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url;
    parse_url(url, &parsed_url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Not redirecting: %s\n", url);
    }
}

int main() {
    const char *url = "http://example.com/some/path";
    redirect_url(url);
    return 0;
}