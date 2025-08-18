#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char *host_start, *host_end;
    
    // Find the start of the host in the URL
    if (strncmp(url, "http://", 7) == 0) {
        host_start = url + 7;
    } else if (strncmp(url, "https://", 8) == 0) {
        host_start = url + 8;
    } else {
        printf("Invalid protocol\n");
        return;
    }

    // Find the end of the host in the URL
    host_end = strchr(host_start, '/');
    if (!host_end) {
        host_end = host_start + strlen(host_start);
    }

    char host[1024];
    strncpy(host, host_start, host_end - host_start);
    host[host_end - host_start] = '\0';

    // Check if the domain is example.com
    if (strcmp(host, domain) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    const char *test_url = "http://example.com/path/to/resource";
    redirect_invalid_url(test_url);

    const char *invalid_url = "http://wrongdomain.com/path/to/resource";
    redirect_invalid_url(invalid_url);

    return 0;
}