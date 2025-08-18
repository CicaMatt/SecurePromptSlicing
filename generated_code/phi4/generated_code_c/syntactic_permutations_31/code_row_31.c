#include <stdio.h>
#include <string.h>

typedef struct {
    char scheme[256];
    char netloc[256];
} ParsedURL;

ParsedURL urlparse(const char* url) {
    ParsedURL parsed;
    const char* delimiter = "://";
    char* token = strstr(url, delimiter);
    if (token != NULL) {
        strncpy(parsed.scheme, url, token - url);
        parsed.scheme[token - url] = '\0';
        token += strlen(delimiter);
        char* netloc_start = token;
        char* path_start = strchr(token, '/');
        if (path_start != NULL) {
            strncpy(parsed.netloc, netloc_start, path_start - netloc_start);
            parsed.netloc[path_start - netloc_start] = '\0';
        } else {
            strcpy(parsed.netloc, netloc_start);
        }
    }
    return parsed;
}

void redirect_url(const char* url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    redirect_url("http://example.com/test");
    redirect_url("https://anotherdomain.com/resource");
    return 0;
}