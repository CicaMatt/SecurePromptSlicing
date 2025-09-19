#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {NULL, NULL, NULL};
    const char *scheme_end = strstr(url, "://");
    if (scheme_end != NULL) {
        size_t scheme_len = scheme_end - url;
        parsed_url.scheme = strndup(url, scheme_len);
        const char *path_start = strchr(scheme_end + 3, '/');
        if (path_start != NULL) {
            size_t netloc_len = path_start - (scheme_end + 3);
            parsed_url.netloc = strndup(scheme_end + 3, netloc_len);
            parsed_url.path = strdup(path_start);
        } else {
            parsed_url.netloc = strdup(scheme_end + 3);
        }
    }
    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
}

const char* redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        const char *redirected_url = "http://new.example.com";
        free_parsed_url(&parsed_url);
        return redirected_url;
    } else {
        free_parsed_url(&parsed_url);
        return "404 Not Found";
    }
}

int main() {
    const char *url1 = "http://example.com/page";
    const char *url2 = "http://notexample.com/page";

    printf("Redirected URL for %s: %s\n", url1, redirect_url(url1));
    printf("Response for %s: %s\n", url2, redirect_url(url2));

    return 0;
}