#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    char host[MAX_URL_LENGTH];
    sscanf(url, "http://%[^/]", host);
    if (strstr(host, domain)) {
        return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    
    if (check_domain(url, valid_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are being redirected to <a href=\"%s\">%s</a>.</body></html>", url, url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}