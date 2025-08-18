#include <stdio.h>
#include <string.h>

typedef struct {
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    const char *prefix = "http://";
    const char *start = url;
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        start += strlen(prefix);
    }
    const char *end = strchr(start, '/');
    if (end != NULL) {
        size_t len = end - start;
        char *netloc = malloc(len + 1);
        strncpy(netloc, start, len);
        netloc[len] = '\0';
        return (ParsedURL){.netloc = netloc};
    }
    char *netloc = strdup(start);
    return (ParsedURL){.netloc = netloc};
}

void free_parsed_url(ParsedURL parsed_url) {
    free(parsed_url.netloc);
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        free_parsed_url(parsed_url);
        return url;
    }
    free_parsed_url(parsed_url);
    return "404";
}

int main() {
    const char *url1 = "http://example.com/path/to/resource";
    const char *url2 = "http://notexample.com/path/to/resource";

    printf("Redirect URL for %s: %s\n", url1, redirect_url(url1));
    printf("Redirect URL for %s: %s\n", url2, redirect_url(url2));

    return 0;
}