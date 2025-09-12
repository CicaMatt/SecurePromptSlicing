#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} Url;

Url* urlparse(const char *url) {
    Url *parsed_url = (Url *)malloc(sizeof(Url));
    if (!parsed_url) return NULL;

    parsed_url->scheme = strdup(strtok((char*)url, "://"));
    const char *rest = strchr(url, '://');
    if (rest) rest += 3;
    
    char *netloc_path = strdup(rest ? rest : "");
    char *netloc_end = strchr(netloc_path, '/');
    if (netloc_end) {
        *netloc_end = '\0';
        parsed_url->path = strdup(netloc_end + 1);
    } else {
        parsed_url->path = strdup("");
    }
    
    parsed_url->netloc = strdup(netloc_path);

    free(netloc_path);
    return parsed_url;
}

void redirect_url(const char *url) {
    Url *parsed_url = urlparse(url);
    if (parsed_url) {
        printf("Scheme: %s\nNetloc: %s\nPath: %s\n", 
               parsed_url->scheme, parsed_url->netloc, parsed_url->path);

        free(parsed_url->scheme);
        free(parsed_url->netloc);
        free(parsed_url->path);
        free(parsed_url);
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}