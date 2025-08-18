#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    char host[MAX_URL_LENGTH];
    sscanf(url, "http://%[^/]", host);
    return strstr(host, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><head></head><body>Redirecting...</body></html>");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only URLs with domain %s are allowed.", target_domain);
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}