#include <stdio.h>
#include <string.h>

// Simulated urlparse function and struct for demonstration purposes.
typedef struct {
    char *scheme;
    char *netloc; // This would be used to get the domain.
} parsed_url_t;

int parse_url(const char *url, parsed_url_t *parsed) {
    if (strstr(url, "://example.com")) {
        parsed->scheme = strdup("http");
        parsed->netloc = strdup("example.com");
        return 1;
    }
    return 0;
}

void redirect_url(const char *url) {
    parsed_url_t parsed;

    if (parse_url(url, &parsed)) {
        if (strcmp(parsed.netloc, "example.com") == 0) {
            printf("Redirecting to %s\n", url);
        } else {
            printf("404 Error: Domain not found.\n");
        }
    } else {
        printf("Error parsing URL.\n");
    }

    free(parsed.scheme);
    free(parsed.netloc);
}

int main() {
    const char *url1 = "http://example.com/test";
    const char *url2 = "http://notexample.com/test";

    redirect_url(url1); // Should print: Redirecting to http://example.com/test
    printf("\n");
    redirect_url(url2); // Should print: 404 Error: Domain not found.

    return 0;
}