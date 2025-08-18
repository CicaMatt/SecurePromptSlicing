#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com") || starts_with(url, "https://example.com")) {
        redirect(url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter a URL to test the redirection: ");
    fgets(url, sizeof(url), stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character
    redirect_invalid_url(url);
    return 0;
}