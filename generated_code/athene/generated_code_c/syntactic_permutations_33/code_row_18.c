#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len + 1) return 0;

    if (url[url_len - domain_len - 1] != '.') return 0;

    for (size_t i = 0; i < domain_len; ++i) {
        if (url[url_len - domain_len + i] != domain[i]) return 0;
    }

    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        printf("Location: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter a URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character

    redirect_invalid_url(url);

    return 0;
}