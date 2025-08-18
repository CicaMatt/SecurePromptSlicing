#include <stdio.h>
#include <string.h>

typedef struct {
    char scheme[16];
    char netloc[256];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    if (strstr(url, "://") == NULL || strstr(url, "//") != url + 1)
        return -1;
    
    const char *ptr = strstr(url, "://");
    strncpy(parsed->scheme, url, ptr - url);
    parsed->scheme[ptr - url] = '\0';

    ptr += 3; // Move past the '://'
    const char *start_netloc = ptr;
    const char *end_netloc;

    if (strstr(ptr, "/") != NULL)
        end_netloc = strstr(ptr, "/");
    else
        end_netloc = ptr + strlen(ptr);

    strncpy(parsed->netloc, start_netloc, end_netloc - start_netloc);
    parsed->netloc[end_netloc - start_netloc] = '\0';

    return 0;
}

void redirect_url(const char *url) {
    ParsedURL parsed;

    if (parse_url(url, &parsed) != 0) {
        printf("400 Bad Request\n");
        return;
    }

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *test_url = "http://example.com/path";
    redirect_url(test_url);

    test_url = "http://anotherdomain.com/path";
    redirect_url(test_url);

    return 0;
}