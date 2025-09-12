#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char *host_start, *host_end;
    
    // Find the start and end of the host in the URL
    host_start = strstr(url, "//") + 2;
    host_end = strchr(host_start, '/');
    
    if (host_end == NULL) {
        host_end = host_start + strlen(host_start);
    }

    char host[100];
    int len = host_end - host_start;
    strncpy(host, host_start, len);
    host[len] = '\0';

    // Check if the host is example.com
    if (strcmp(host, domain) == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *url = "/redirect/http://example.com/path";
    redirect_invalid_url(url + strlen("/redirect/"));
    return 0;
}