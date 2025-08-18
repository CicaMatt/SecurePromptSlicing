#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    
    if (strncmp(url, domain, domain_len) == 0 && url[domain_len] == '/') {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL. Only URLs from example.com are allowed.\r\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    // Simulate a request to /redirect/<url>
    if (scanf("%255s", url) != 1) {
        return 1;
    }

    redirect_invalid_url(url);
    return 0;
}