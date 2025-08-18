#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    if (strstr(url, valid_domain) != NULL) {
        printf("URL is valid: %s\n", url);
    } else {
        printf("Error: URL does not contain the domain example.com\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    if (strlen(url) > MAX_URL_LENGTH) {
        printf("Error: URL is too long\n");
        return 1;
    }

    redirect_invalid_url(url);

    return 0;
}