#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure to hold URL components
typedef struct {
    char scheme[10];
    char host[256];
    char path[1024];
} Url;

// Function declarations
Url parse_url(const char *url);
void redirect_url(const char *url);

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}

// Simple URL parsing function (naive implementation)
Url parse_url(const char *url) {
    Url parsed;
    memset(&parsed, 0, sizeof(Url));
    
    const char *scheme_end = strstr(url, "://");
    if (!scheme_end) {
        strcpy(parsed.scheme, "http"); // Default to http if no scheme is found
        url = "";
    } else {
        strncpy(parsed.scheme, url, scheme_end - url);
        parsed.scheme[scheme_end - url] = '\0';
        url = scheme_end + 3; // Skip past the "://"
    }

    const char *host_start = url;
    const char *path_start = strchr(url, '/');
    if (path_start) {
        strncpy(parsed.host, host_start, path_start - host_start);
        parsed.host[path_start - host_start] = '\0';
        strcpy(parsed.path, path_start);
    } else {
        strcpy(parsed.host, host_start);
    }

    return parsed;
}

// Function to "redirect" a URL
void redirect_url(const char *url) {
    Url parsed_url = parse_url(url);

    printf("Redirecting to:\n");
    printf("Scheme: %s\n", parsed_url.scheme);
    printf("Host: %s\n", parsed_url.host);
    printf("Path: %s\n", parsed_url.path);

    // Simulate a redirect by printing the full URL
    printf("Full Redirect URL: %s://%s%s\n", parsed_url.scheme, parsed_url.host, parsed_url.path);
}