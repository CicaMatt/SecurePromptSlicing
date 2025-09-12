#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define URL_MAX_LENGTH 256

typedef struct {
    char scheme[32];
    char netloc[64];
    char path[128];
    char params[64];
    char query[64];
    char fragment[64];
} ParsedURL;

void urlparse(const char *url, ParsedURL *parsed_url) {
    const char *scheme_end = strchr(url, ':');
    if (scheme_end) {
        strncpy(parsed_url->scheme, url, scheme_end - url);
        parsed_url->scheme[scheme_end - url] = '\0';
        const char *netloc_start = strstr(scheme_end + 1, "//");
        if (netloc_start) {
            netloc_start += 2;
            const char *path_start = strchr(netloc_start, '/');
            if (path_start) {
                strncpy(parsed_url->netloc, netloc_start, path_start - netloc_start);
                parsed_url->netloc[path_start - netloc_start] = '\0';
                strncpy(parsed_url->path, path_start, URL_MAX_LENGTH - 1);
            } else {
                strcpy(parsed_url->netloc, netloc_start);
                strcpy(parsed_url->path, "");
            }
        } else {
            strcpy(parsed_url->netloc, scheme_end + 1);
            strcpy(parsed_url->path, "");
        }
    }
}

void redirect_url(const char *url) {
    ParsedURL parsed_url;
    urlparse(url, &parsed_url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char url[URL_MAX_LENGTH];
    printf("Enter URL: ");
    if (fgets(url, sizeof(url), stdin)) {
        // Remove newline character from the end of the input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        redirect_url(url);
    }
    return 0;
}