#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    size_t url_len = strlen(url);

    if (url_len >= domain_len && strcmp(url + url_len - domain_len, domain) == 0) {
        return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url)) {
        printf("Location: %s\r\nContent-Type: text/html\r\n\r\nRedirecting to %s...\r\n", url, url);
    } else {
        printf("Status: 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid URL domain.\r\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    // Simulating receiving a URL parameter
    strcpy(url, "http://example.com");

    redirect_invalid_url(url);

    return 0;
}