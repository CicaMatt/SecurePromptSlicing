#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {NULL, NULL};
    char *scheme, *netloc, *temp_url;
    
    temp_url = strdup(url);
    scheme = strtok(temp_url, "://");
    netloc = strtok(NULL, "/");
    
    if (scheme && netloc) {
        parsed_url.scheme = strdup(scheme);
        parsed_url.netloc = strdup(netloc);
    }
    
    free(temp_url);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
    
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    redirect_url(argv[1]);
    return 0;
}