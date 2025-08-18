#include <stdio.h>
#include <string.h>

typedef struct {
    char scheme[16];
    char netloc[256];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *proto_end = strstr(url, "://");
    if (!proto_end) return 0;
    
    int proto_len = proto_end - url + strlen("://");
    strncpy(parsed->scheme, url, proto_len);
    parsed->scheme[proto_len] = '\0';

    const char *netloc_start = proto_end + strlen("://");
    const char *path_start = strchr(netloc_start, '/');
    
    if (!path_start) path_start = netloc_start + strlen(netloc_start);

    strncpy(parsed->netloc, netloc_start, path_start - netloc_start);
    parsed->netloc[path_start - netloc_start] = '\0';

    return 1;
}

void redirect_url(const char *url) {
    ParsedURL parsed;
    
    if (!parse_url(url, &parsed)) {
        printf("Error parsing URL\n");
        return;
    }

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *test_url = "http://example.com/path";
    redirect_url(test_url);

    const char *another_url = "https://not-example.com/path";
    redirect_url(another_url);

    return 0;
}