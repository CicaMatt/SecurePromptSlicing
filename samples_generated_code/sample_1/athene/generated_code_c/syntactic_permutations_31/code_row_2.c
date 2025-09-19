#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed_url = {0};
    const char *scheme_delim = "://";
    const char *slash_delim = "/";
    
    char *scheme_start = (char *)url;
    char *scheme_end = strstr(scheme_start, scheme_delim);
    if (scheme_end) {
        int scheme_len = scheme_end - scheme_start;
        parsed_url.scheme = malloc((scheme_len + 1) * sizeof(char));
        strncpy(parsed_url.scheme, url, scheme_len);
        parsed_url.scheme[scheme_len] = '\0';
        
        char *netloc_start = scheme_end + strlen(scheme_delim);
        char *netloc_end = strchr(netloc_start, '/');
        if (!netloc_end) {
            netloc_end = netloc_start + strlen(netloc_start);
        }
        int netloc_len = netloc_end - netloc_start;
        parsed_url.netloc = malloc((netloc_len + 1) * sizeof(char));
        strncpy(parsed_url.netloc, netloc_start, netloc_len);
        parsed_url.netloc[netloc_len] = '\0';
    }

    return parsed_url;
}

void free_parsed_url(ParsedUrl *parsed_url) {
    if (parsed_url->scheme) free(parsed_url->scheme);
    if (parsed_url->netloc) free(parsed_url->netloc);
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Not redirecting: %s\n", url);
    }
    
    free_parsed_url(&parsed_url);
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "https://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}