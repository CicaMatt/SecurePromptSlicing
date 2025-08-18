#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mocking urlparse function for demonstration purposes
typedef struct {
    char* scheme;
    char* netloc;
    char* path;
} ParsedURL;

ParsedURL* urlparse(const char* url) {
    ParsedURL* parsed_url = (ParsedURL*)malloc(sizeof(ParsedURL));
    parsed_url->scheme = strtok((char*)url, "://");
    parsed_url->netloc = strtok(NULL, "/");
    parsed_url->path = strtok(NULL, "");
    return parsed_url;
}

void free_parsed_url(ParsedURL* parsed_url) {
    free(parsed_url);
}

int redirect_url(const char* url) {
    ParsedURL* parsed_url = urlparse(url);
    if (strcmp(parsed_url->netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
        free_parsed_url(parsed_url);
        return 1; // Redirect successful
    } else {
        printf("404 Not Found\n");
        free_parsed_url(parsed_url);
        return 0; // 404 error
    }
}

int main() {
    const char* test_url = "http://example.com/page";
    redirect_url(test_url);

    const char* invalid_url = "http://notexample.com/page";
    redirect_url(invalid_url);

    return 0;
}