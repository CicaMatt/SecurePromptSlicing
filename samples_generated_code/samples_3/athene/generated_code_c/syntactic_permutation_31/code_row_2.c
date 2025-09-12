#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedURL;

ParsedURL urlparse(const char* url) {
    ParsedURL parsed_url = {0};
    char *scheme, *netloc;
    scheme = strdup(url);
    netloc = strchr(scheme, ':');
    if (netloc) {
        *netloc++ = '\0';
        netloc = strchr(netloc + 3, '/');
        if (netloc) {
            *netloc++ = '\0';
        }
    }
    parsed_url.scheme = scheme;
    parsed_url.netloc = strdup(scheme + strlen(parsed_url.scheme) + 1);
    return parsed_url;
}

void free_parsed_url(ParsedURL* parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
}

int redirect_url(const char* url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
        free_parsed_url(&parsed_url);
        return 1;
    }
    free_parsed_url(&parsed_url);
    return 0;
}

int main() {
    const char* test_url = "http://example.com/path";
    redirect_url(test_url);
    return 0;
}