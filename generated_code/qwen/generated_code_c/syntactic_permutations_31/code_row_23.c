#include <stdio.h>
#include <string.h>

typedef struct {
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    // Simplified urlparse function for demonstration purposes
    const char *prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    }
    char *slash = strchr(url, '/');
    if (slash != NULL) {
        size_t len = slash - url;
        char *netloc = malloc(len + 1);
        strncpy(netloc, url, len);
        netloc[len] = '\0';
        return (ParsedURL){.netloc = netloc};
    }
    return (ParsedURL){.netloc = strdup(url)};
}

void free_parsed_url(ParsedURL parsed_url) {
    free(parsed_url.netloc);
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        free_parsed_url(parsed_url);
        return "http://new-example.com";
    } else {
        free_parsed_url(parsed_url);
        return "404 Not Found";
    }
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://notexample.com/path";

    printf("Redirected URL for %s: %s\n", url1, redirect_url(url1));
    printf("Redirected URL for %s: %s\n", url2, redirect_url(url2));

    return 0;
}