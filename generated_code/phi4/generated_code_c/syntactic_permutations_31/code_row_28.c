#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL urlparse(const char* url) {
    ParsedURL result = {0};
    const char *delimiter = "://";
    char *temp_url = strdup(url);

    // Extract scheme
    char *scheme_end = strstr(temp_url, delimiter);
    if (scheme_end) {
        size_t len = scheme_end - temp_url;
        result.scheme = strndup(temp_url, len);
        *(char *)(scheme_end) = '\0';  // Null-terminate the scheme part

        // Move pointer past "://"
        char *netloc_start = scheme_end + strlen(delimiter);

        // Extract netloc
        char *path_start = strchr(netloc_start, '/');
        if (path_start) {
            size_t len = path_start - netloc_start;
            result.netloc = strndup(netloc_start, len);
            *(char *)(path_start) = '\0';  // Null-terminate the netloc part

            // Extract path
            result.path = strdup(path_start + 1);
        } else {
            result.netloc = strdup(netloc_start);
        }
    }

    free(temp_url);
    return result;
}

void redirect_url(const char* url) {
    ParsedURL parsed_url = urlparse(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("No redirection. Domain is not example.com.\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
    free(parsed_url.path);
}

int main() {
    const char* test_url1 = "http://example.com/path/to/resource";
    const char* test_url2 = "https://anotherdomain.com/path";

    redirect_url(test_url1);  // Expected to redirect
    redirect_url(test_url2);  // Expected not to redirect

    return 0;
}