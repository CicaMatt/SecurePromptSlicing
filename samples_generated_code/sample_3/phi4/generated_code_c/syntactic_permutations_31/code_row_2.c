#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed;
    const char *scheme_delim = "://";
    const char *netloc_delim = "/";

    // Allocate memory for the netloc
    parsed.netloc = (char *)malloc(strlen(url) + 1);

    // Find scheme and netloc
    const char *start = url;
    if ((parsed.scheme = strstr(start, scheme_delim))) {
        *parsed.scheme = '\0'; // Terminate the previous part
        start = parsed.scheme + strlen(scheme_delim);
    }
    
    const char *end = strchr(start, '/');
    if (end) {
        strncpy(parsed.netloc, start, end - start);
        parsed.netloc[end - start] = '\0';
    } else {
        strcpy(parsed.netloc, start); // Copy the rest as netloc
    }

    // Allocate memory for path, set to empty if not found
    parsed.path = "/";
    
    return parsed;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting: %s\n", url);
    } else {
        printf("No redirection needed for URL: %s\n", url);
    }

    free(parsed_url.netloc); // Free allocated memory
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "https://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}