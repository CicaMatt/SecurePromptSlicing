#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len + 1) return 0;
    if (url[url_len - domain_len - 1] != '.') return 0;

    for (size_t i = 0; i < domain_len; i++) {
        if (tolower(url[url_len - domain_len + i]) != tolower(domain[i])) {
            return 0;
        }
    }

    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}