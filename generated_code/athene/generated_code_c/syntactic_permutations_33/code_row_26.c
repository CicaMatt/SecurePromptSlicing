#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int contains_domain(const char *url, const char *domain) {
    char host[MAX_URL_LENGTH];
    sscanf(url, "http://%[^/]", host);
    if (strstr(host, domain)) return 1;
    return 0;
}

void redirect_invalid_url(const char *url) {
    if (contains_domain(url, "example.com")) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        exit(0);
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Usage: /redirect?url=URL\n");
        return 1;
    }

    redirect_invalid_url(argv[1]);
    return 0;
}