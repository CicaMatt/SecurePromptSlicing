#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    size_t domain_len = strlen(domain);
    if (strlen(url) < domain_len + 7) return 0; // Check minimum length for "http://"
    if (strncmp(url + strlen(url) - domain_len, domain, domain_len) == 0) return 1;
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("HTTP/1.1 302 Found\n");
        printf("\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Invalid URL domain.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character

    redirect_invalid_url(url);

    return 0;
}