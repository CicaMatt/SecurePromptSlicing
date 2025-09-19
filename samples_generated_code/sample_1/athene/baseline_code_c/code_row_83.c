#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len + 7) return 0; // Check for minimum length
    if (strncmp(url + url_len - domain_len, domain, domain_len) != 0) return 0;
    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    if (check_domain(url, valid_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);
    return 0;
}