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

    // Find the end of scheme
    end = strchr(start, ':');
    if (end) {
        parsed_url.scheme = strndup(start, end - start);
        start = end + 3; // skip "://"
    }

    // Find the end of netloc
    end = strchr(start, '/');
    if (!end) end = url + strlen(url);
    parsed_url.netloc = strndup(start, end - start);

    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Not redirecting: %s\n", url);
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}