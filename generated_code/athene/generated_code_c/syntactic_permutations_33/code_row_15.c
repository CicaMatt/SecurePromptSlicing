#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    int url_len = strlen(url);
    int domain_len = strlen(domain);

    if (url_len < domain_len + 1 || url[url_len - domain_len - 1] != '.') return 0;
    for (int i = 0; i < domain_len; i++) {
        if (url[url_len - domain_len + i] != domain[i]) return 0;
    }
    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    if (check_domain(url, valid_domain)) {
        printf("Location: http://valid-destination.com/\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>You have been redirected.</body></html>");
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error: Invalid URL domain.");
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