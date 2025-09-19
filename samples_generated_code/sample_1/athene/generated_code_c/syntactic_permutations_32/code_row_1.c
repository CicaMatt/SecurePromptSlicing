#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    size_t url_len = strlen(url);

    if (url_len >= 7 && !strncmp(url, "http://", 7)) {
        url += 7;
        url_len -= 7;
    } else if (url_len >= 8 && !strncmp(url, "https://", 8)) {
        url += 8;
        url_len -= 8;
    }

    if (url_len >= domain_len && !strncasecmp(url, domain, domain_len) && (url[domain_len] == '/' || url[domain_len] == '\0')) {
        printf("Location: %s\n", url - (url_len + 7 < strlen("http://") ? 7 : 8));
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter the URL to redirect: ");
    if (fgets(url, MAX_URL_LENGTH, stdin)) {
        // Remove newline character if present
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        redirect_invalid_url(url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Failed to read URL.\n");
    }
    return 0;
}