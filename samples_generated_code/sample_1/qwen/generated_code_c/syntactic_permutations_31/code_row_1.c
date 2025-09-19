#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} UrlParseResult;

UrlParseResult urlparse(const char *url) {
    UrlParseResult result = {0};
    const char *p = url;
    if (strncmp(p, "http://", 7) == 0 || strncmp(p, "https://", 8) == 0) {
        p += strcspn(p, "//") + 2;
    }
    result.netloc = strdup(p);
    const char *end = strchr(result.netloc, '/');
    if (end) {
        *(char*)end = '\0';
    }
    return result;
}

const char* redirect_url(const char *url) {
    UrlParseResult parsed_url = urlparse(url);
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        free(parsed_url.netloc);
        return "Redirecting...";
    } else {
        free(parsed_url.netloc);
        return "404 Error";
    }
}

int main() {
    const char *url1 = "http://example.com/some/path";
    const char *url2 = "https://anotherdomain.com/page";

    printf("%s\n", redirect_url(url1));
    printf("%s\n", redirect_url(url2));

    return 0;
}