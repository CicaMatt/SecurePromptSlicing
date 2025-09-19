#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    size_t domain_len = strlen(domain);
    size_t url_len = strlen(url);

    if (url_len < domain_len + 1) return 0;

    const char *last_slash = strrchr(url, '/');
    const char *check_start = last_slash ? last_slash + 1 : url;

    if (strstr(check_start, domain)) {
        return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    if (check_domain(url, valid_domain)) {
        printf("Location: https://www.%s/\r\n", valid_domain);
        printf("\r\n");
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\r\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    if (fgets(url, MAX_URL_LENGTH, stdin)) {
        // Remove newline character
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        redirect_invalid_url(url);
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: No URL provided.\r\n");
    }
    return 0;
}