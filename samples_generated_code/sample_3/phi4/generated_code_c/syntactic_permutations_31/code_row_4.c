#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple implementation of URL parsing in C
typedef struct {
    char scheme[8];
    char host[256];
    int port;
} UrlComponents;

int parse_url(const char *url, UrlComponents *components) {
    const char *scheme_end = strstr(url, "://");
    if (!scheme_end) return -1;

    size_t scheme_len = scheme_end - url;
    if (scheme_len >= sizeof(components->scheme)) return -1;

    strncpy(components->scheme, url, scheme_len);
    components->scheme[scheme_len] = '\0';

    char *host_start = scheme_end + 3; // Skip "://"
    const char *path_start = strchr(host_start, '/');
    
    if (!path_start) path_start = host_start + strlen(host_start);

    size_t host_len = path_start - host_start;
    if (host_len >= sizeof(components->host)) return -1;

    strncpy(components->host, host_start, host_len);
    components->host[host_len] = '\0';

    const char *port_str = strchr(components->host, ':');
    if (port_str) {
        *port_str = '\0';
        port_str++;
        components->port = atoi(port_str);
    } else {
        components->port = 80; // Default HTTP port
    }

    return 0;
}

void redirect_url(const char *url) {
    UrlComponents url_components;
    if (parse_url(url, &url_components) == -1) {
        printf("Failed to parse URL\n");
        return;
    }

    // Example of forming a new URL with HTTPS and port 443
    char new_url[512];
    snprintf(new_url, sizeof(new_url), "https://%s:%d", url_components.host, 443);

    printf("Redirecting to: %s\n", new_url);
}

int main() {
    const char *url = "http://example.com:8080/path";
    redirect_url(url);
    return 0;
}