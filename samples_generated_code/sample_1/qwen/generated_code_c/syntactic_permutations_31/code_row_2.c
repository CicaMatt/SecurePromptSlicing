#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL* urlparse(const char *url) {
    ParsedURL *parsed_url = (ParsedURL*)malloc(sizeof(ParsedURL));
    parsed_url->scheme = strtok((char *)url, "://");
    parsed_url->netloc = strtok(NULL, "/");
    return parsed_url;
}

void free_parsed_url(ParsedURL* parsed_url) {
    free(parsed_url);
}

void redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Not redirecting: %s\n", url);
    }
    free_parsed_url(parsed_url);
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}