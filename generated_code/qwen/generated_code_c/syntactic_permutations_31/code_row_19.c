#include <stdio.h>
#include <string.h>

typedef struct {
    const char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    // Simplified urlparse function for demonstration purposes
    const char *prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    }
    const char *end = strchr(url, '/');
    size_t len = end ? (size_t)(end - url) : strlen(url);
    static char netloc[256];
    strncpy(netloc, url, len);
    netloc[len] = '\0';
    return (ParsedURL){.netloc = netloc};
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url1 = "http://example.com/somepage";
    const char *url2 = "http://notexample.com/anotherpage";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}