#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed = {0};
    char *temp = strdup(url);
    char *token = strtok(temp, "://");
    if (token != NULL) {
        parsed.scheme = strdup(token);
        token = strtok(NULL, "/");
        if (token != NULL) {
            parsed.netloc = strdup(token);
            char *path_start = strchr(token, '/');
            if (path_start != NULL) {
                path_start++;
                parsed.path = strdup(path_start);
            }
        }
    }
    free(temp);
    return parsed;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    printf("%s\n", parsed_url.netloc);
    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}