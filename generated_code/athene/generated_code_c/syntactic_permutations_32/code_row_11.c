#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    if (strlen(url) >= domain_len + 7 && strncmp(url, "http://", 7) == 0) {
        if (strncmp(url + 7, domain, domain_len) == 0) {
            printf("Location: %s\n", url);
            printf("Content-Type: text/html\n");
            printf("\n");
            return;
        }
    } else if (strlen(url) >= domain_len + 8 && strncmp(url, "https://", 8) == 0) {
        if (strncmp(url + 8, domain, domain_len) == 0) {
            printf("Location: %s\n", url);
            printf("Content-Type: text/html\n");
            printf("\n");
            return;
        }
    }

    printf("HTTP/1.1 400 Bad Request\n");
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("Error: Invalid URL domain.\n");
}

int main() {
    char url[MAX_URL_LENGTH];
    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character
        url[strcspn(url, "\n")] = 0;
        redirect_invalid_url(url);
    }
    return 0;
}