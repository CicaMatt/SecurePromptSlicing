#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    char url[MAX_URL_LENGTH];
    strncpy(url, argv[1], MAX_URL_LENGTH);
    url[MAX_URL_LENGTH - 1] = '\0';

    redirect_invalid_url(url);

    return 0;
}