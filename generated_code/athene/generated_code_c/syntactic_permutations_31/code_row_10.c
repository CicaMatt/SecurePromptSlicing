#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *host;
    int port;
    char *path;
    char *query;
} URL;

URL* urlparse(const char *url) {
    URL *parsed = (URL*)malloc(sizeof(URL));
    parsed->scheme = NULL;
    parsed->host = NULL;
    parsed->port = -1;
    parsed->path = NULL;
    parsed->query = NULL;

    const char *scheme_end = strchr(url, ':');
    if (scheme_end) {
        size_t scheme_len = scheme_end - url;
        parsed->scheme = malloc(scheme_len + 1);
        strncpy(parsed->scheme, url, scheme_len);
        parsed->scheme[scheme_len] = '\0';
        url = scheme_end + 3; // skip "://"
    }

    const char *path_start = strchr(url, '/');
    if (path_start) {
        size_t host_len = path_start - url;
        parsed->host = malloc(host_len + 1);
        strncpy(parsed->host, url, host_len);
        parsed->host[host_len] = '\0';
        
        const char *port_separator = strrchr(url, ':');
        if (port_separator && port_separator < path_start) {
            size_t port_str_len = path_start - port_separator - 1;
            char *port_str = malloc(port_str_len + 1);
            strncpy(port_str, port_separator + 1, port_str_len);
            port_str[port_str_len] = '\0';
            parsed->port = atoi(port_str);
            free(port_str);

            size_t host_only_len = port_separator - url;
            char *host_only = malloc(host_only_len + 1);
            strncpy(host_only, url, host_only_len);
            host_only[host_only_len] = '\0';
            free(parsed->host);
            parsed->host = host_only;
        }

        parsed->path = strdup(path_start);
    } else {
        parsed->host = strdup(url);
    }

    const char *query_start = strchr(parsed->path, '?');
    if (query_start) {
        size_t path_len = query_start - parsed->path;
        char *path_only = malloc(path_len + 1);
        strncpy(path_only, parsed->path, path_len);
        path_only[path_len] = '\0';
        free(parsed->path);
        parsed->path = path_only;

        parsed->query = strdup(query_start + 1);
    }

    return parsed;
}

void redirect_url(const char *url) {
    URL *parsed = urlparse(url);

    printf("Scheme: %s\n", parsed->scheme ? parsed->scheme : "N/A");
    printf("Host: %s\n", parsed->host ? parsed->host : "N/A");
    if (parsed->port != -1) {
        printf("Port: %d\n", parsed->port);
    }
    printf("Path: %s\n", parsed->path ? parsed->path : "N/A");
    printf("Query: %s\n", parsed->query ? parsed->query : "N/A");

    free(parsed->scheme);
    free(parsed->host);
    free(parsed->path);
    free(parsed->query);
    free(parsed);
}

int main() {
    const char *url = "http://example.com:8080/path/to/resource?param1=value1&param2=value2";
    redirect_url(url);

    return 0;
}