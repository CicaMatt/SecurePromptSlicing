#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed;
    const char *http_pos = strstr(url, "://");
    const char *start_netloc = (http_pos == NULL) ? url : http_pos + 3;
    const char *end_netloc = strstr(start_netloc, "/");

    if (end_netloc != NULL) {
        int netloc_len = end_netloc - start_netloc;
        parsed.netloc = (char *)malloc(netloc_len + 1);
        strncpy(parsed.netloc, start_netloc, netloc_len);
        parsed.netloc[netloc_len] = '\0';
    } else {
        size_t len = strlen(start_netloc);
        parsed.netloc = (char *)malloc(len + 1);
        strcpy(parsed.netloc, start_netloc);
    }

    if (http_pos != NULL) {
        int scheme_len = http_pos - url;
        parsed.scheme = (char *)malloc(scheme_len + 1);
        strncpy(parsed.scheme, url, scheme_len);
        parsed.scheme[scheme_len] = '\0';
    } else {
        parsed.scheme = strdup("http");
    }

    return parsed;
}

void free_parsed_url(ParsedURL *parsed) {
    if (parsed->scheme != NULL) {
        free((void *)parsed->scheme);
    }
    if (parsed->netloc != NULL) {
        free((void *)parsed->netloc);
    }
}

int redirect_url(const char *url) {
    ParsedURL parsed = parse_url(url);

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not found.\n");
    }

    free_parsed_url(&parsed);

    return 0;
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "https://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}