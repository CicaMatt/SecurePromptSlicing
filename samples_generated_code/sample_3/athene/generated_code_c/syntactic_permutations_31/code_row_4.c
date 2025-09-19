#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *host;
    char *path;
} Url;

Url* urlparse(const char *url) {
    Url *parsed_url = (Url*)malloc(sizeof(Url));
    parsed_url->scheme = strdup(strtok((char *)url, "://"));
    parsed_url->host = strdup(strtok(NULL, "/"));
    parsed_url->path = strdup(strtok(NULL, ""));
    return parsed_url;
}

void redirect_url(const char *url) {
    Url *parsed = urlparse(url);
    printf("Redirecting to: %s://%s%s\n", parsed->scheme, parsed->host, parsed->path);
    free(parsed->scheme);
    free(parsed->host);
    free(parsed->path);
    free(parsed);
}

int main() {
    redirect_url("https://example.com/path");
    return 0;
}