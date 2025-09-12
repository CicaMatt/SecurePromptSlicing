#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url;
    char *temp = strdup(url);
    char *token = strtok(temp, "://");
    if (token != NULL) {
        parsed_url.scheme = token;
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed_url.netloc = token;
        } else {
            parsed_url.netloc = "";
        }
    } else {
        parsed_url.scheme = "";
        parsed_url.netloc = temp;
    }
    free(temp);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "http://example.com";
    redirect_url(url);
    return 0;
}