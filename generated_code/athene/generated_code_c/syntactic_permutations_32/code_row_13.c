#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com") || starts_with(url, "https://example.com")) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><head></head><body>Redirecting...</body></html>");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only URLs from example.com are allowed.");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character

    redirect_invalid_url(url);

    return 0;
}