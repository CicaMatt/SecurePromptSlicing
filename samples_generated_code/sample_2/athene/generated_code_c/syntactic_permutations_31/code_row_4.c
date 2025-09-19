#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *host;
    char *path;
} URL;

URL *urlparse(const char *url) {
    URL *parsed_url = (URL *)malloc(sizeof(URL));
    parsed_url->scheme = NULL;
    parsed_url->host = NULL;
    parsed_url->path = NULL;

    const char *scheme_delim = "://";
    const char *slash_delim = "/";

    char *url_copy = strdup(url);
    if (strstr(url, scheme_delim) != NULL) {
        parsed_url->scheme = strtok(url_copy, scheme_delim);
        url_copy += strlen(parsed_url->scheme) + strlen(scheme_delim);
    }

    char *host_path = url_copy;
    const char *slash_pos = strchr(host_path, '/');
    if (slash_pos != NULL) {
        int host_len = slash_pos - host_path;
        parsed_url->host = (char *)malloc(host_len + 1);
        strncpy(parsed_url->host, host_path, host_len);
        parsed_url->host[host_len] = '\0';
        parsed_url->path = strdup(slash_pos);
    } else {
        parsed_url->host = strdup(host_path);
    }

    return parsed_url;
}

void redirect_url(const char *url) {
    URL *parsed_url = urlparse(url);
    if (parsed_url != NULL && parsed_url->scheme != NULL && parsed_url->host != NULL) {
        printf("Redirecting to: %s://%s\n", parsed_url->scheme, parsed_url->host);
    } else {
        printf("Invalid URL\n");
    }
    free(parsed_url->scheme);
    free(parsed_url->host);
    free(parsed_url->path);
    free(parsed_url);
}

int main() {
    const char *url = "https://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}