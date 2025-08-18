#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "http://example.com";
    
    if (starts_with(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return EXIT_SUCCESS;
}