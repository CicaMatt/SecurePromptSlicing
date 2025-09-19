#include <stdio.h>
#include <string.h>

typedef struct {
    const char *scheme;
    const char *netloc;
    const char *path;
    const char *params;
    const char *query;
    const char *fragment;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed_url = {0};
    // This is a very basic parser and doesn't handle all edge cases.
    char url_copy[2048];
    strncpy(url_copy, url, sizeof(url_copy));
    
    const char *scheme_end = strstr(url_copy, "://");
    if (scheme_end) {
        *scheme_end = '\0';
        parsed_url.scheme = url_copy;
        scheme_end += 3; // Move past '://'
        
        const char *path_start = strchr(scheme_end, '/');
        if (path_start) {
            *path_start = '\0';
            parsed_url.netloc = scheme_end;
            path_start++; // Move to start of the path
            
            const char *query_start = strchr(path_start, '?');
            if (query_start) {
                *query_start = '\0';
                parsed_url.path = path_start;
                query_start++;
                
                const char *fragment_start = strchr(query_start, '#');
                if (fragment_start) {
                    *fragment_start = '\0';
                    parsed_url.query = query_start;
                    fragment_start++;
                    
                    parsed_url.fragment = fragment_start;
                } else {
                    parsed_url.query = query_start;
                }
            } else {
                parsed_url.path = path_start;
            }
        } else {
            parsed_url.netloc = scheme_end;
        }
    }
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);
    
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error 404: Not Found\n");
    }
}

int main() {
    const char *url1 = "http://example.com/path?query=value#fragment";
    const char *url2 = "http://anotherdomain.com/path?query=value";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}