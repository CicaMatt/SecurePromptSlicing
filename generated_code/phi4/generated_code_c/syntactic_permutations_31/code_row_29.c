#include <stdio.h>
#include <string.h>

// Mock function for urlparse and parsing URL to simulate Python's urlparse functionality.
typedef struct {
    char* netloc;
} ParsedUrl;

ParsedUrl mock_urlparse(const char *url) {
    ParsedUrl parsed;
    // Simplified check assuming "http://example.com/path" as input format
    if (strncmp(url, "http://", 7) == 0 && strstr(url + 7, ".com") != NULL) {
        const char* start = url + 7; // Skip "http://"
        const char* end = strchr(start, '/');
        if (end) {
            parsed.netloc = strndup(start, end - start);
        } else {
            parsed.netloc = strdup(start); // Copy the whole string if no '/' found
        }
    } else {
        parsed.netloc = NULL;
    }
    return parsed;
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = mock_urlparse(url);
    
    if (parsed_url.netloc && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Returning: %s\n", url);
    }
    
    free(parsed_url.netloc); // Free memory allocated by strndup or strdup
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://anotherdomain.com/path");
    return 0;
}