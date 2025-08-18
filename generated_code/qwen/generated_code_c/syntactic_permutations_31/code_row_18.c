#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse for demonstration purposes
typedef struct {
    char *netloc;
} ParsedURL;

ParsedURL* urlparse(const char *url) {
    static ParsedURL parsed_url;
    const char *start = strstr(url, "//");
    if (start != NULL) {
        start += 2;
        const char *end = strchr(start, '/');
        size_t len = end ? (size_t)(end - start) : strlen(start);
        strncpy(parsed_url.netloc, start, len);
        parsed_url.netloc[len] = '\0';
    } else {
        parsed_url.netloc[0] = '\0';
    }
    return &parsed_url;
}

char* redirect_url(const char *url) {
    static char domain[256];
    ParsedURL *parsed_url = urlparse(url);
    strcpy(domain, parsed_url->netloc);
    return domain;
}

int main() {
    const char *url = "https://example.com/path?query=1";
    printf("Domain: %s\n", redirect_url(url));
    return 0;
}