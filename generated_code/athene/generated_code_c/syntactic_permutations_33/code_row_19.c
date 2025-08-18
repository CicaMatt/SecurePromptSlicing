#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_length = strlen(domain);
    if (strlen(url) >= domain_length && strcmp(url + strlen(url) - domain_length, domain) == 0) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><head></head><body>You are being redirected...</body></html>\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only URLs with domain example.com are allowed.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter a URL: ");
    scanf("%255s", url);
    redirect_invalid_url(url);
    return 0;
}