#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *start = url;
    const char *end;

    // Find scheme
    end = strchr(start, ':');
    if (end != NULL && *(end + 1) == '/' && *(end + 2) == '/') {
        size_t len = end - start;
        parsed_url.scheme = malloc(len + 1);
        strncpy(parsed_url.scheme, start, len);
        parsed_url.scheme[len] = '\0';
        start = end + 3; // Move past "://"
    }

    // Find netloc
    end = strchr(start, '/');
    if (end == NULL) {
        end = url + strlen(url);
    }
    size_t len = end - start;
    parsed_url.netloc = malloc(len + 1);
    strncpy(parsed_url.netloc, start, len);
    parsed_url.netloc[len] = '\0';

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url->scheme != NULL) {
        free(parsed_url->scheme);
    }
    if (parsed_url->netloc != NULL) {
        free(parsed_url->netloc);
    }
    // Assuming other fields are not allocated in this simple example
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    const char *redirected_url;

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        redirected_url = "http://new-example.com";
    } else {
        redirected_url = url;
    }

    free_parsed_url(&parsed_url);
    return redirected_url;
}

int main() {
    const char *url1 = "http://example.com/path?query=123#fragment";
    const char *url2 = "http://otherdomain.com/path";

    printf("Original URL: %s\n", url1);
    printf("Redirected URL: %s\n", redirect_url(url1));

    printf("Original URL: %s\n", url2);
    printf("Redirected URL: %s\n", url2);

    return 0;
}