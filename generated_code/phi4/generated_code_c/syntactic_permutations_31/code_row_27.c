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
    ParsedURL parsed;
    const char *netloc_start = strstr(url, "://") + 3;
    const char *netloc_end = strchr(netloc_start, '/');
    
    if (!netloc_end) netloc_end = url + strlen(url);
    
    size_t netloc_length = netloc_end - netloc_start;
    parsed.netloc = (char *)malloc(netloc_length + 1);
    strncpy(parsed.netloc, netloc_start, netloc_length);
    parsed.netloc[netloc_length] = '\0';
    
    parsed.scheme = NULL;
    if (strncmp(url, "http://", 7) == 0) {
        parsed.scheme = "http";
    } else if (strncmp(url, "https://", 8) == 0) {
        parsed.scheme = "https";
    }
    
    parsed.path = netloc_end;
    parsed.params = NULL;
    parsed.query = strchr(parsed.path, '?');
    if (parsed.query) {
        *parsed.query++ = '\0';
    } else {
        parsed.query = "";
    }
    
    parsed.fragment = strchr(parsed.query, '#');
    if (parsed.fragment) {
        *parsed.fragment++ = '\0';
    } else {
        parsed.fragment = "";
    }

    return parsed;
}

void redirect_url(const char *url) {
    ParsedURL parsed = parse_url(url);
    
    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Domain is not example.com. No redirection.\n");
    }
    
    free((void *)parsed.netloc);
}

int main() {
    const char *url = "http://example.com/path?query=1#fragment";
    redirect_url(url);

    return 0;
}