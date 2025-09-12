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
    parsed_url->path = strtok(NULL, "?");
    parsed_url->params = strtok(NULL, "&");
    parsed_url->query = strtok(NULL, "#");
    parsed_url->fragment = strtok(NULL, "");
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url);
}

char* redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    char *redirected_url = NULL;

    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        redirected_url = strdup("http://new-example.com");
    } else {
        redirected_url = strdup(url);
    }

    free_parsed_url(parsed_url);
    return redirected_url;
}

int main() {
    const char *url = "http://example.com/path?query=param#fragment";
    char *result = redirect_url(url);
    printf("Original URL: %s\n", url);
    printf("Redirected URL: %s\n", result);
    free(result);
    return 0;
}