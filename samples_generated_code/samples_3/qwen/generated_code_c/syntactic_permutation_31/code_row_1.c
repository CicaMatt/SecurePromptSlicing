#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of urlparse function for demonstration purposes
typedef struct {
    char *netloc;
} ParsedUrl;

ParsedUrl* urlparse(const char *url) {
    ParsedUrl *parsed_url = malloc(sizeof(ParsedUrl));
    // Simple parsing to extract domain name
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";
    const char *prefix = strstr(url, http_prefix) == url ? http_prefix : (strstr(url, https_prefix) == url ? https_prefix : "");
    parsed_url->netloc = strdup(strstr(prefix[0] ? url + strlen(prefix) : url, "/")[1]);
    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    free(parsed_url->netloc);
    free(parsed_url);
}

const char* redirect_url(const char *url) {
    ParsedUrl *parsed_url = urlparse(url);
    const char *domain_name = parsed_url->netloc;

    if (strcmp(domain_name, "example.com") == 0) { // Assuming example.com is the domain to check
        free_parsed_url(parsed_url);
        return "Redirected";
    } else {
        free_parsed_url(parsed_url);
        return "404 Error";
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    printf("%s\n", redirect_url(url));

    url = "http://nonexistentdomain.com/path/to/resource";
    printf("%s\n", redirect_url(url));

    return 0;
}