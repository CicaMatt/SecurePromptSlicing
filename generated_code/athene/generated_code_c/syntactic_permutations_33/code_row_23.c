#include <stdio.h>
#include <string.h>

#define MAX_URL_LEN 256

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);
    if (url_len < domain_len + 1) return 0;
    if (url[url_len - domain_len - 1] != '.') return 0;
    return strncmp(url + url_len - domain_len, domain, domain_len) == 0;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

int main() {
    char input_url[MAX_URL_LEN];
    printf("Enter a URL: ");
    fgets(input_url, MAX_URL_LEN, stdin);
    input_url[strcspn(input_url, "\n")] = 0; // Remove newline
    redirect_invalid_url(input_url);
    return 0;
}