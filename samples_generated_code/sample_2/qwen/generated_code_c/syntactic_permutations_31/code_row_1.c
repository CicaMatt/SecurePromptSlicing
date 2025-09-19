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
    ParsedURL *parsed_url = malloc(sizeof(ParsedURL));
    if (parsed_url == NULL) return NULL;

    parsed_url->scheme = strtok((char *)url, "://");
    parsed_url->netloc = strtok(NULL, "/");
    parsed_url->path = strtok(NULL, "?");
    parsed_url->params = strtok(NULL, "&");
    parsed_url->query = strtok(NULL, "#");
    parsed_url->fragment = strtok(NULL, "");

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url != NULL) {
        free(parsed_url);
    }
}

const char* redirect_url(const char *url) {
    ParsedURL *parsed_url = urlparse(url);
    const char *domain = parsed_url->netloc;

    if (strcmp(domain, "example.com") == 0) {
        return "Redirected to example.com";
    } else {
        return "404 Not Found";
    }

    free_parsed_url(parsed_url);
}

int main() {
    const char *url1 = "http://example.com/path?query=param#fragment";
    const char *url2 = "http://otherdomain.com/path";

    printf("%s\n", redirect_url(url1));
    printf("%s\n", redirect_url(url2));

    return 0;
}