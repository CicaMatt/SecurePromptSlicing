#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedURL;

ParsedURL urlparse(const char* url) {
    ParsedURL parsed_url = {0};
    char* dup = strdup(url);
    char* scheme_end = strchr(dup, ':');
    if (scheme_end) {
        *scheme_end = '\0';
        parsed_url.scheme = strdup(dup);
        parsed_url.netloc = scheme_end + 3; // Skip "://"
    } else {
        parsed_url.netloc = strdup(url);
    }
    free(dup);
    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Not redirecting: Domain is not example.com\n");
    }
    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char* test_url = "http://example.com";
    redirect_url(test_url);
    return 0;
}