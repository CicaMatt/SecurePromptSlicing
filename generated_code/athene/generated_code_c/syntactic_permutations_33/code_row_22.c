#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    size_t domain_len = strlen(domain);
    if (strlen(url) < domain_len + 7) return 0; // Minimum length for http://example.com
    if (strstr(url, domain) == url + 7) return 1;
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL domain.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    scanf("%255s", url);
    redirect_invalid_url(url);
    return 0;
}