#include <stdio.h>
#include <string.h>

typedef struct {
    const char *scheme;
    const char *netloc;
    const char *path;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *start, *end;

    start = url;
    end = strchr(start, ':');
    if (end != NULL && *(end + 1) == '/' && *(end + 2) == '/') {
        parsed_url.scheme = strndup(start, end - start);
        start = end + 3;
        end = strchr(start, '/');
        if (end != NULL) {
            parsed_url.netloc = strndup(start, end - start);
            parsed_url.path = strdup(end);
        } else {
            parsed_url.netloc = strdup(start);
        }
    }

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url->scheme != NULL) free((char*)parsed_url->scheme);
    if (parsed_url->netloc != NULL) free((char*)parsed_url->netloc);
    if (parsed_url->path != NULL) free((char*)parsed_url->path);
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: http://%s%s\n", parsed_url.netloc, parsed_url.path);
    } else {
        printf("404 Error: Not Found\n");
    }

    free_parsed_url(&parsed_url);
}

int main() {
    const char *url1 = "http://example.com/some/path";
    const char *url2 = "http://notexample.com/another/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}