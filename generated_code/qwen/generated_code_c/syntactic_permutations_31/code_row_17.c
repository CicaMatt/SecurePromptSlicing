#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse function
typedef struct {
    char* scheme;
    char* netloc;
    char* path;
} ParsedURL;

ParsedURL urlparse(const char* url) {
    ParsedURL parsed_url = {"http", "", ""};
    const char* prefix = "http://";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    }
    const char* end = strchr(url, '/');
    if (end != NULL) {
        size_t len = end - url;
        parsed_url.netloc = strndup(url, len);
        parsed_url.path = strdup(end);
    } else {
        parsed_url.netloc = strdup(url);
    }
    return parsed_url;
}

void free_parsed_url(ParsedURL* parsed_url) {
    free(parsed_url->netloc);
    free(parsed_url->path);
}

int redirect_url(const char* url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: http://%s%s\n", parsed_url.netloc, parsed_url.path);
        free_parsed_url(&parsed_url);
        return 0;
    } else {
        free_parsed_url(&parsed_url);
        return 404;
    }
}

int main() {
    const char* test_url = "http://example.com/some/path";
    int result = redirect_url(test_url);
    if (result == 404) {
        printf("404 Not Found\n");
    }

    const char* invalid_url = "http://notexample.com/another/path";
    result = redirect_url(invalid_url);
    if (result == 404) {
        printf("404 Not Found\n");
    }

    return 0;
}