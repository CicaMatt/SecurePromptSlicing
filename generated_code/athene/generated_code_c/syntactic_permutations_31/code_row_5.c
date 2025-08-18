#include <stdio.h>
#include <string.h>

typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    char *domain = strrchr(url, '//');
    if (domain != NULL) {
        domain += 2; // Skip "//"
        char *path = strchr(domain, '/');
        if (path != NULL) {
            *path = '\0';
        }
        parsed_url.netloc = strdup(domain);
    } else {
        parsed_url.netloc = strdup(url);
    }
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
    free(parsed_url.netloc);
}

int main() {
    const char* test_url = "http://example.com/path";
    redirect_url(test_url);
    return 0;
}