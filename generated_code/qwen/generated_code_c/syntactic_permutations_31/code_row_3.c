#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL result = {0};
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";
    
    const char *start = url;
    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        start += strlen(http_prefix);
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        start += strlen(https_prefix);
    }
    
    const char *end = strchr(start, '/');
    if (!end) {
        end = url + strlen(url);
    }
    
    result.netloc = strndup(start, end - start);
    return result;
}

void free_parsed_url(ParsedURL parsed_url) {
    free(parsed_url.netloc);
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    const char *domain = parsed_url.netloc;
    
    if (strcmp(domain, "example.com") == 0) {
        free_parsed_url(parsed_url);
        return "Redirecting to example.com";
    } else {
        free_parsed_url(parsed_url);
        return "404 Not Found";
    }
}

int main() {
    const char *url1 = "http://example.com/some/path";
    const char *url2 = "https://notexample.com/another/path";
    
    printf("%s\n", redirect_url(url1));
    printf("%s\n", redirect_url(url2));
    
    return 0;
}