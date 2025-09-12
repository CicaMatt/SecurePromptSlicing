#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char scheme[16];
    char host[256];
    int port;
    char path[1024];
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL result = {0};
    
    const char *scheme_end = strchr(url, ':');
    if (scheme_end != NULL && strncmp(scheme_end - 2, "://", 3) == 0) {
        strncpy(result.scheme, url, scheme_end - url);
        result.scheme[scheme_end - url] = '\0';
        
        const char *host_start = scheme_end + 3;
        const char *path_start = strchr(host_start, '/');
        if (path_start != NULL) {
            int host_length = path_start - host_start;
            strncpy(result.host, host_start, host_length);
            result.host[host_length] = '\0';
            
            const char *port_start = strchr(result.host, ':');
            if (port_start != NULL) {
                *port_start = '\0'; // Terminate the host part
                result.port = atoi(port_start + 1);
            } else {
                result.port = 80; // Default port for HTTP
            }
            
            strcpy(result.path, path_start);
        } else {
            int host_length = strlen(host_start);
            strncpy(result.host, host_start, host_length);
            result.host[host_length] = '\0';
            
            const char *port_start = strchr(result.host, ':');
            if (port_start != NULL) {
                *port_start = '\0'; // Terminate the host part
                result.port = atoi(port_start + 1);
            } else {
                result.port = 80; // Default port for HTTP
            }
            
            strcpy(result.path, "/");
        }
    }
    
    return result;
}

void redirect_url(const char *url) {
    ParsedURL parsed = urlparse(url);
    printf("Redirecting to %s://%s:%d%s\n", parsed.scheme, parsed.host, parsed.port, parsed.path);
}

int main() {
    const char *test_url = "http://www.example.com:8080/path/to/resource";
    redirect_url(test_url);
    return 0;
}