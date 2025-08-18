#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char *url) {
    ParsedUrl parsed = { .scheme = NULL, .netloc = NULL };
    const char *scheme_delim = "://";
    char *domain_delim = "/";
    
    char *scheme_start = (char *)url;
    char *scheme_end = strstr(scheme_start, scheme_delim);
    if (scheme_end) {
        parsed.scheme = strndup(scheme_start, scheme_end - scheme_start);
        
        char *netloc_start = scheme_end + strlen(scheme_delim);
        char *netloc_end = strchr(netloc_start, '/');
        if (!netloc_end) netloc_end = netloc_start + strlen(netloc_start);

        parsed.netloc = strndup(netloc_start, netloc_end - netloc_start);
    }
    return parsed;
}

void free_parsed_url(ParsedUrl *parsed) {
    if (parsed->scheme) free(parsed->scheme);
    if (parsed->netloc) free(parsed->netloc);
}

void redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 Error: Domain not found\n");
    }
    
    free_parsed_url(&parsed_url);
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);
    return 0;
}