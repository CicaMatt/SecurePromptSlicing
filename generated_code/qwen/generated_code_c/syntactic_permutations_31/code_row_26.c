#include <stdio.h>
#include <string.h>

typedef struct {
    char *netloc;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *scheme_end = strstr(url, "://");
    if (scheme_end != NULL) {
        scheme_end += 3;
        const char *path_start = strchr(scheme_end, '/');
        if (path_start != NULL) {
            size_t netloc_len = path_start - scheme_end;
            parsed_url.netloc = (char *)malloc(netloc_len + 1);
            strncpy(parsed_url.netloc, scheme_end, netloc_len);
            parsed_url.netloc[netloc_len] = '\0';
        } else {
            parsed_url.netloc = strdup(scheme_end);
        }
    }
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    if (parsed_url->netloc != NULL) {
        free(parsed_url->netloc);
        parsed_url->netloc = NULL;
    }
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        const char *redirected_url = "http://new-example.com";
        free_parsed_url(&parsed_url);
        return redirected_url;
    } else {
        free_parsed_url(&parsed_url);
        return "404 Not Found";
    }
}

int main() {
    const char *url1 = "http://example.com/path/to/resource";
    const char *url2 = "http://another-example.com/path/to/resource";

    printf("Redirected URL for %s: %s\n", url1, redirect_url(url1));
    printf("Redirected URL for %s: %s\n", url2, redirect_url(url2));

    return 0;
}