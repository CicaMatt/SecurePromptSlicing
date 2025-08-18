#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *netloc;
} ParsedUrl;

ParsedUrl parse_url(const char *url) {
    ParsedUrl parsed_url;
    char *domain = strstr(url, "//") + 2;
    if (strstr(domain, "/")) {
        domain = strndup(domain, strstr(domain, "/") - domain);
    } else {
        domain = strdup(domain);
    }
    parsed_url.netloc = domain;
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = parse_url(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/somepath";
    redirect_url(url);
    return 0;
}