#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy struct and function definitions for illustration
typedef struct {
    char *netloc;
} ParsedUrl;

ParsedUrl parse_url(const char *url) {
    ParsedUrl parsed_url;
    
    // A naive way to extract the domain name; real implementation would be more complex
    const char *start = strstr(url, "://");
    if (start) {
        start += 3; // Move past '://'
    } else {
        start = url;
    }

    const char *end = strchr(start, '/');
    if (!end) {
        end = start + strlen(start);
    }
    
    size_t len = end - start;
    parsed_url.netloc = (char *)malloc(len + 1);
    strncpy(parsed_url.netloc, start, len);
    parsed_url.netloc[len] = '\0';
    
    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    if (parsed_url->netloc) {
        free(parsed_url->netloc);
    }
}

int redirect_url(const char *url) {
    ParsedUrl parsed_url = parse_url(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }

    free_parsed_url(&parsed_url);
    return 0;
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://anotherdomain.com/path";

    redirect_url(url1); // Should redirect
    redirect_url(url2); // Should return a 404 error

    return 0;
}