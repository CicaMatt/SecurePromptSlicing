#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);
    if (url_len < domain_len + 7 || strncmp(url + url_len - domain_len - 7, "http://", 7) != 0 && strncmp(url + url_len - domain_len - 8, "https://", 8) != 0) {
        return 0;
    }
    return !strcmp(url + url_len - domain_len, domain);
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        exit(0);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n\n");
        printf("Error: No URL provided.\n");
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}