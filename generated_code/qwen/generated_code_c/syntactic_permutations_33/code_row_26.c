#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url) {
    const char *domain = "example.com";
    return strstr(url, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url)) {
        printf("Location: %s\r\n\r\n", url);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        redirect_invalid_url(url);
    }
    return 0;
}