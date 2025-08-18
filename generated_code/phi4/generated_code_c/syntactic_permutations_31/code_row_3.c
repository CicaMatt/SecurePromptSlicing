#include <stdio.h>
#include <string.h>

typedef struct {
    const char *scheme;
    const char *netloc;
    const char *path;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL result = {0};
    const char *start = url;
    
    // Parse scheme
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        result.scheme = start;
        start += (strcmp(start, "http://") == 0) ? 7 : 8;
    }
    
    // Parse netloc
    const char *netloc_start = strchr(start, '/');
    if (!netloc_start) netloc_start = strpbrk(start, "\r\n\0");
    result.netloc = start;
    *strtok(netloc_start, "/ \t\r\n") = '\0';
    
    // Parse path
    result.path = (netloc_start ? netloc_start : url + strlen(url));
    
    return result;
}

int redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);
    
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url); // Simulate redirection
        return 302; // HTTP status code for redirect
    } else {
        printf("404 Not Found\n");
        return 404; // HTTP status code for not found
    }
}

int main() {
    const char *url1 = "http://example.com/path/to/resource";
    const char *url2 = "http://anotherdomain.com/path/to/resource";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}