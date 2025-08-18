#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} URLParsed;

URLParsed urlparse(const char *url) {
    URLParsed parsed = {0};
    char *temp = strdup(url);
    char *token = strtok(temp, "://");
    if (token != NULL) {
        parsed.scheme = strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed.netloc = strdup(token);
        }
    }
    free(temp);
    return parsed;
}

void redirect_url(const char *url) {
    URLParsed parsed = urlparse(url);
    if (parsed.netloc == NULL) {
        printf("404 Not Found\n");
        return;
    }

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }

    free(parsed.scheme);
    free(parsed.netloc);
}

int main() {
    const char *url = "http://example.com";
    redirect_url(url);
    return 0;
}