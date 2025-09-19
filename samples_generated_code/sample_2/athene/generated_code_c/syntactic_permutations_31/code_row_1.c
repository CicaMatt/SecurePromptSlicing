#include <stdio.h>
#include <string.h>

typedef struct {
    char* scheme;
    char* netloc;
} ParsedUrl;

ParsedUrl urlparse(const char* url) {
    ParsedUrl parsed_url = { .scheme = NULL, .netloc = NULL };
    const char* proto_end = strstr(url, "://");
    if (proto_end == NULL) return parsed_url;
    
    int proto_len = proto_end - url;
    parsed_url.scheme = malloc(proto_len + 1);
    strncpy(parsed_url.scheme, url, proto_len);
    parsed_url.scheme[proto_len] = '\0';

    const char* domain_start = proto_end + 3; // Skip "://"
    const char* domain_end = strchr(domain_start, '/');
    
    int domain_len;
    if (domain_end == NULL) {
        domain_len = strlen(domain_start);
    } else {
        domain_len = domain_end - domain_start;
    }
    
    parsed_url.netloc = malloc(domain_len + 1);
    strncpy(parsed_url.netloc, domain_start, domain_len);
    parsed_url.netloc[domain_len] = '\0';

    return parsed_url;
}

void redirect_url(const char* url) {
    ParsedUrl parsed_url = urlparse(url);

    if (parsed_url.scheme == NULL || parsed_url.netloc == NULL) {
        printf("404 Not Found\n");
        return;
    }

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }

    free(parsed_url.scheme);
    free(parsed_url.netloc);
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://notexample.com/path");
    return 0;
}