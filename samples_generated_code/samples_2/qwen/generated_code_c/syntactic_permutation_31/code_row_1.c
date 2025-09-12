#include <stdio.h>
#include <string.h>

// Mock implementation of urlparse function for demonstration purposes
typedef struct {
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url;
    // Simple parsing logic to extract netloc, assuming format "http://example.com/path"
    const char *protocol_end = strstr(url, "://") + 3;
    const char *path_start = strchr(protocol_end, '/');
    if (path_start == NULL) {
        parsed_url.netloc = strdup(protocol_end);
    } else {
        parsed_url.netloc = strndup(protocol_end, path_start - protocol_end);
    }
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: http://redirected-example.com\n");
    } else {
        printf("404 Not Found\n");
    }
    free(parsed_url.netloc);
}

int main() {
    redirect_url("http://example.com/path/to/resource");
    redirect_url("http://anotherdomain.com/path/to/resource");
    return 0;
}