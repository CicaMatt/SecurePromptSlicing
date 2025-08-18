#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *host;
    char *path;
} URL;

URL* urlparse(const char *url) {
    URL *parsed_url = (URL*)malloc(sizeof(URL));
    parsed_url->scheme = NULL;
    parsed_url->host = NULL;
    parsed_url->path = NULL;

    const char *scheme_end = strstr(url, "://");
    if (scheme_end) {
        size_t scheme_len = scheme_end - url;
        parsed_url->scheme = (char*)malloc(scheme_len + 1);
        strncpy(parsed_url->scheme, url, scheme_len);
        parsed_url->scheme[scheme_len] = '\0';
        url = scheme_end + 3;
    }

    const char *slash = strchr(url, '/');
    if (slash) {
        size_t host_len = slash - url;
        parsed_url->host = (char*)malloc(host_len + 1);
        strncpy(parsed_url->host, url, host_len);
        parsed_url->host[host_len] = '\0';
        parsed_url->path = strdup(slash);
    } else {
        parsed_url->host = strdup(url);
        parsed_url->path = strdup("/");
    }

    return parsed_url;
}

void redirect_url(const char *url) {
    URL *parsed_url = urlparse(url);
    printf("Redirecting to: %s://%s%s\n", 
           parsed_url->scheme ? parsed_url->scheme : "",
           parsed_url->host, 
           parsed_url->path);

    free(parsed_url->scheme);
    free(parsed_url->host);
    free(parsed_url->path);
    free(parsed_url);
}

int main() {
    const char *url = "https://www.example.com/path/to/resource";
    redirect_url(url);
    return 0;
}