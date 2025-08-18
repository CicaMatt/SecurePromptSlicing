#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    return strstr(url, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("HTTP/1.1 301 Moved Permanently\nLocation: http://example.com/\n\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nInvalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return EXIT_SUCCESS;
}