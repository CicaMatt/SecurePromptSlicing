#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} Url;

Url urlparse(const char* url) {
    Url parsed_url;
    const char* scheme_delim = "://";
    const char* path_delim = "/";
    parsed_url.scheme = strtok((char*)url, scheme_delim);
    if (parsed_url.scheme != NULL) {
        char* netloc_and_path = strtok(NULL, "");
        if (netloc_and_path != NULL) {
            parsed_url.netloc = strtok(netloc_and_path, path_delim);
        } else {
            parsed_url.netloc = "";
        }
    } else {
        parsed_url.scheme = "";
        parsed_url.netloc = (char*)url;
    }
    return parsed_url;
}

void redirect_url(const char* url) {
    Url parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
}

int main() {
    redirect_url("http://example.com/path/to/resource");
    return 0;
}