#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char scheme[MAX_URL_LENGTH];
    char netloc[MAX_URL_LENGTH];
    char path[MAX_URL_LENGTH];
    char params[MAX_URL_LENGTH];
    char query[MAX_URL_LENGTH];
    char fragment[MAX_URL_LENGTH];
} ParsedURL;

void urlparse(const char *url, ParsedURL *parsed_url) {
    const char *scheme_end = strchr(url, ':');
    if (scheme_end != NULL) {
        strncpy(parsed_url->scheme, url, scheme_end - url);
        parsed_url->scheme[scheme_end - url] = '\0';
        
        const char *netloc_start = scheme_end + 3; // Skip "://"
        const char *path_start = strchr(netloc_start, '/');
        if (path_start != NULL) {
            strncpy(parsed_url->netloc, netloc_start, path_start - netloc_start);
            parsed_url->netloc[path_start - netloc_start] = '\0';
            
            strncpy(parsed_url->path, path_start, MAX_URL_LENGTH);
        } else {
            strcpy(parsed_url->netloc, netloc_start);
            parsed_url->path[0] = '\0';
        }
    }
}

void redirect_url(const char *url) {
    ParsedURL parsed_url;
    urlparse(url, &parsed_url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: https://new.example.com\n");
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "http://example.com/some/path";
    redirect_url(url);
    
    return 0;
}