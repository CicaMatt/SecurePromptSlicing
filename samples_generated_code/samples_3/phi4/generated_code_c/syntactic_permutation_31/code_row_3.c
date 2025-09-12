#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc; // Network location (domain)
} ParsedURL;

ParsedURL parse_url(const char *url) {
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";

    ParsedURL parsed_url;
    parsed_url.scheme = NULL;
    parsed_url.netloc = NULL;

    // Check scheme
    if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
        parsed_url.scheme = strdup("http");
        url += strlen(http_prefix);
    } else if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
        parsed_url.scheme = strdup("https");
        url += strlen(https_prefix);
    }

    // Find netloc
    char *netloc_start = strstr(url, "//");
    if (netloc_start != NULL) {
        netloc_start += 2; // Skip the "//"
        char *end_of_netloc = strchr(netloc_start, '/');
        if (end_of_netloc != NULL) {
            size_t len = end_of_netloc - netloc_start;
            parsed_url.netloc = strndup(netloc_start, len);
        } else {
            parsed_url.netloc = strdup(netloc_start);
        }
    }

    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (parsed_url.netloc != NULL && strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    char url1[] = "http://example.com/page";
    char url2[] = "https://anotherdomain.com/page";

    redirect_url(url1); // Should print: Redirecting to http://example.com/page
    printf("\n");
    redirect_url(url2); // Should print: 404 Not Found

    return 0;
}