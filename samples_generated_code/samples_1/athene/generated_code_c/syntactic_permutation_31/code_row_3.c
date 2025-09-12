#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = { .netloc = NULL };
    char* temp = strdup(url);
    char* scheme = strtok(temp, "://");
    if (scheme != NULL) {
        char* rest = strtok(NULL, "/");
        if (rest != NULL) {
            parsed_url.netloc = strdup(rest);
        }
    }
    free(temp);
    return parsed_url;
}

void free_parsed_url(ParsedUrl* parsed_url) {
    free(parsed_url->netloc);
}

int redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
        free_parsed_url(&parsed_url);
        return 302;
    } else {
        printf("404 Not Found\n");
        free_parsed_url(&parsed_url);
        return 404;
    }
}

int main() {
    const char* test_url = "http://example.com";
    redirect_url(test_url);
    return 0;
}