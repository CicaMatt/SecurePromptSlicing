#include <stdio.h>
#include <string.h>

typedef struct {
    char scheme[16];
    char netloc[256];
    char path[256];
    char params[256];
    char query[256];
    char fragment[256];
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    sscanf(url, "%15[^:]://%255[^/]%255[^?]%255[^#]%255[#]", 
           parsed_url.scheme, parsed_url.netloc, parsed_url.path, parsed_url.params, parsed_url.query, parsed_url.fragment);
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