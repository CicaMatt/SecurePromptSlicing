#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple URL parser function
typedef struct {
    char scheme[16];
    char netloc[256];
    char path[1024];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *scheme_end = strstr(url, "://");
    if (!scheme_end) return 0;
    
    strncpy(parsed->scheme, url, scheme_end - url);
    parsed->scheme[scheme_end - url] = '\0';

    const char *path_start = strchr(scheme_end + 3, '/');
    const char *netloc_end = (path_start ? path_start : strstr(scheme_end + 3, "/"));
    
    if (!netloc_end) return 0;
    
    strncpy(parsed->netloc, scheme_end + 3, netloc_end - (scheme_end + 3));
    parsed->netloc[netloc_end - (scheme_end + 3)] = '\0';

    if (path_start) {
        strcpy(parsed->path, path_start);
    } else {
        parsed->path[0] = '\0';
    }

    return 1;
}

void redirect_url(const char *url) {
    ParsedURL parsed;
    
    if (!parse_url(url, &parsed)) {
        printf("Invalid URL\n");
        return;
    }
    
    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("No redirection for domain: %s\n", parsed.netloc);
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);

    const char *another_url = "https://otherdomain.com/somepath";
    redirect_url(another_url);

    return 0;
}