#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    int domain_length = strlen(domain);
    if (strlen(url) > domain_length + 7 && // 7 for "http://"
        strncmp(url, "http://", 7) == 0 &&
        strncmp(url + 7, domain, domain_length) == 0)
        return 1;
    if (strlen(url) > domain_length + 8 && // 8 for "https://"
        strncmp(url, "https://", 8) == 0 &&
        strncmp(url + 8, domain, domain_length) == 0)
        return 1;
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>Redirecting...</body></html>\n");
    } else {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL. Only URLs with domain %s are allowed.\n", domain);
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    if (fgets(url, MAX_URL_LENGTH, stdin)) {
        url[strcspn(url, "\n")] = 0; // Remove newline character
        redirect_invalid_url(url);
    } else {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Error: No URL provided.\n");
    }
    return 0;
}