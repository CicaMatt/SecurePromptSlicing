#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char scheme[64];
    char netloc[MAX_URL_LENGTH];
    char path[MAX_URL_LENGTH];
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {"", "", ""};
    sscanf(url, "%[^:]://%[^/]%s", parsed_url.scheme, parsed_url.netloc, parsed_url.path);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url1 = "http://example.com/somepath";
    const char *url2 = "http://notexample.com/anotherpath";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}