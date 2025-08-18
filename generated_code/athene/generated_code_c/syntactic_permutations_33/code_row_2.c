#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    int url_len = strlen(url);
    int domain_len = strlen(domain);

    if (url_len < domain_len + 7) { // Minimum length for http://example.com
        return 0;
    }

    const char *start = url + url_len - domain_len;

    if (strncmp(start, domain, domain_len) == 0) {
        return 1;
    }

    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    
    if (check_domain(url, valid_domain)) {
        printf("Location: %s\n", url);
    } else {
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    char input_url[MAX_URL_LENGTH];
    printf("Enter a URL: ");
    fgets(input_url, MAX_URL_LENGTH, stdin);
    input_url[strcspn(input_url, "\n")] = 0; // Remove newline character

    redirect_invalid_url(input_url);

    return 0;
}