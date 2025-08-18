#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. The URL must contain %s.\n", domain);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char url[MAX_URL_LENGTH];
    strncpy(url, argv[1], MAX_URL_LENGTH);
    url[MAX_URL_LENGTH - 1] = '\0';

    redirect_invalid_url(url);

    return EXIT_SUCCESS;
}