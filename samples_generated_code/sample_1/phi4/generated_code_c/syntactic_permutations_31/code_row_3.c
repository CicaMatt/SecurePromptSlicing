#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL result = {0};
    const char *delimiter = "://";
    
    // Extract scheme
    char *scheme_start = (char *)url;
    char *scheme_end = strstr(url, delimiter);
    if (scheme_end) {
        size_t len = scheme_end - url;
        result.scheme = strndup(scheme_start, len);
    }
    
    // Extract netloc
    char *netloc_start = scheme_end + strlen(delimiter);
    const char *path_delim = "/";
    char *path_start = strchr(netloc_start, '/');
    if (path_start) {
        size_t len = path_start - netloc_start;
        result.netloc = strndup(netloc_start, len);
    } else {
        result.netloc = strdup(netloc_start);
    }
    
    // Extract path
    if (path_start) {
        result.path = strdup(path_start);
    }
    
    return result;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
    free(parsed_url->path);
    free(parsed_url->params);
    free(parsed_url->query);
    free(parsed_url->fragment);
}

int redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);
    
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
        free_parsed_url(&parsed_url);
        return 0; // success
    } else {
        printf("404 Error: Domain not found.\n");
        free_parsed_url(&parsed_url);
        return 1; // error
    }
}

int main() {
    const char *url = "http://example.com/test";
    redirect_url(url);

    const char *url2 = "http://otherdomain.com/test";
    redirect_url(url2);
    
    return 0;
}