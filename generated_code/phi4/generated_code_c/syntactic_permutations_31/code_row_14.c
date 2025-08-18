#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL result = {NULL, NULL};
    const char *temp = strstr(url, "://");
    if (temp) {
        size_t scheme_len = temp - url;
        result.scheme = strndup(url, scheme_len);

        temp += 3; // Move past "://"
        const char *netloc_start = temp;

        temp = strchr(netloc_start, '/');
        if (!temp) {
            temp = netloc_start + strlen(netloc_start);
        }

        size_t netloc_len = temp - netloc_start;
        result.netloc = strndup(netloc_start, netloc_len);
    }
    return result;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (parsed_url.netloc != NULL) {
        printf("Network location: %s\n", parsed_url.netloc);
    } else {
        printf("Invalid URL or missing network location.\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    redirect_url(url);
    return 0;
}