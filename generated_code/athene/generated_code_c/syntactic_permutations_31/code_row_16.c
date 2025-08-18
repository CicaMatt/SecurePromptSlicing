#include <stdio.h>
#include <string.h>

typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url;
    char temp[256];
    sscanf(url, "http://%[^/]", temp);
    parsed_url.netloc = strdup(temp);
    return parsed_url;
}

void free_parsed_url(ParsedUrl parsed_url) {
    if (parsed_url.netloc != NULL) {
        free(parsed_url.netloc);
    }
}

int redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);
    int status;
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
        status = 302; // HTTP Status Code for Redirect
    } else {
        printf("404 Not Found\n");
        status = 404; // HTTP Status Code for Not Found
    }
    free_parsed_url(parsed_url);
    return status;
}

int main() {
    const char* url1 = "http://example.com";
    const char* url2 = "http://notexample.com";

    redirect_url(url1); // Should print: Redirecting to http://example.com and return 302
    redirect_url(url2); // Should print: 404 Not Found and return 404

    return 0;
}