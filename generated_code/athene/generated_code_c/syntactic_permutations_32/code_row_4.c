#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com") || starts_with(url, "https://example.com")) {
        printf("Location: %s\n", url);
        printf("HTTP/1.1 302 Found\n");
        printf("\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    if (scanf("%s", url) != 1) {
        return 1;
    }
    redirect_invalid_url(url);
    return 0;
}